#include "server.h"

/**
 * @brief Creates a new server
 * @param host The host to bind to
 * @param port The port to bind to
 * @param handler The handler function for client connections
 * @return A pointer to the new server
 */
ced_server_p ced_server_new(const char *host, int port, ced_server_handler handler) {
    if (port == 0) {
        return NULL;
    }

    ced_server_p server = malloc(sizeof(ced_server_t));

    if (server == NULL) {
        return NULL;
    }

    ced_reflect_set_info(server, reflect_type_server);

    if (host != NULL) {
        server->host = strdup(host);
    } else {
        server->host = NULL;
    }

    server->port = port;
    server->running = 0;
    server->clients = ced_list_new();
    server->clients->managed_data = 1;
    server->handler = handler;
    server->clients_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

    if (server->clients == NULL) {
        ced_server_free(server);
        return NULL;
    }

    return server;
}

/**
 * @brief Frees a server
 * @param server The server to free
 */
void ced_server_free(ced_server_p server) {
    if (server == NULL) {
        return;
    }

    if (server->host != NULL) {
        free(server->host);
    }

    if (server->clients != NULL) {
        ced_list_free(server->clients);
    }

    pthread_mutex_destroy(&server->clients_mutex);
    free(server);
}

/**
 * @brief Creates a new client
 * @param fd The file descriptor of the client
 * @param host The connecting client
 * @param port The port of the client
 * @return A pointer to the new client
 */
ced_server_client_p ced_server_client_new(int fd, const char *host, int port) {
    if (fd == 0) {
        return NULL;
    }

    ced_server_client_p client = malloc(sizeof(ced_server_client_t));

    if (client == NULL) {
        return NULL;
    }

    ced_reflect_set_info(client, reflect_type_server_client);

    client->fd = fd;
    client->finished = 0;

    if (host != NULL) {
        client->host = strdup(host);
    } else {
        client->host = NULL;
    }

    client->port = port;

    return client;
}

/**
 * @brief Frees a client
 * @param client The client to free
 */
void ced_server_client_free(ced_server_client_p client) {
    if (client == NULL) {
        return;
    }

    if (client->host != NULL) {
        free(client->host);
    }

    free(client);
}

/**
 * @brief Removes all finished clients from the server
 * @param server The server to remove finished clients from
 */
void _ced_server_remove_finished_clients(ced_server_p server) {
    ced_list_node_p client_node;
    ced_list_p clients_to_remove = ced_list_new();
    pthread_mutex_lock(&server->clients_mutex);

    ced_list_foreach(client_node, server->clients) {
        ced_server_client_p client = (ced_server_client_p) client_node->data;

        if (client->finished) {
            ced_list_append(clients_to_remove, client);
        }
    }

    ced_list_foreach(client_node, clients_to_remove) {
        ced_server_client_p client = (ced_server_client_p) client_node->data;
        ced_list_remove(server->clients, NULL, client);
    }

    pthread_mutex_unlock(&server->clients_mutex);
    ced_list_free(clients_to_remove);
}

/**
 * @brief The server loop
 * @param server The server to loop
 * @return 0 on success, -1 on failure
 */
int _ced_server_loop(ced_server_p server) {
    while (server->running) {
        int new_socket;
        struct sockaddr_in address;
        int addr_len = sizeof(address);

        if ((new_socket = accept(server->fd, (struct sockaddr*)&address, (socklen_t*)&addr_len)) < 0) {
            ced_log("Failed to accept: %s\n", strerror(errno));
            return CED_FAILURE;
        }

        ced_server_client_p client = ced_server_client_new(
                new_socket,
                inet_ntoa(address.sin_addr),
                ntohs(address.sin_port)
        );

        client->server = server;

        pthread_mutex_lock(&server->clients_mutex);
        ced_list_append(server->clients, client);
        pthread_mutex_unlock(&server->clients_mutex);

        if (server->handler != NULL) {
            if (pthread_create(
                    &client->thread,
                    NULL,
                    (void *(*)(void *)) server->handler,
                    client) != 0) {
                ced_log("Failed to create thread for client %d\n", client->fd);
            }

            pthread_detach(client->thread);
        }

        _ced_server_remove_finished_clients(server);
    }
}

/**
 * @brief Starts a server
 * @param server The server to start
 * @return 0 on success, -1 on failure
 */
int ced_server_start(ced_server_p server) {
    if (server == NULL) {
        return CED_FAILURE;
    }

    if (server->running) {
        return CED_FAILURE;
    }

    if ((server->fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        ced_log("Failed to start server: %s\n", strerror(errno));
        return CED_FAILURE;
    }

    int opt = 1;
    if (setsockopt(server->fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        ced_log("Failed to set socket options: %s\n", strerror(errno));
        return CED_FAILURE;
    }

    struct sockaddr_in address;

    address.sin_family = AF_INET;

    if (server->host != NULL) {
        address.sin_addr.s_addr = inet_addr(server->host);
    } else {
        address.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    address.sin_port = htons(server->port);

    if (bind(server->fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        ced_log("Failed to bind: %s\n", strerror(errno));
        return CED_FAILURE;
    }

    if (listen(server->fd, 10) < 0) {
        ced_log("Failed to start listening: %s\n", strerror(errno));
        return CED_FAILURE;
    }

    server->running = 1;

    _ced_server_loop(server);

    return CED_SUCCESS;
}

/**
 * @brief Finishes a client connection
 * @param client The client to finish
 * @return 0 on success, -1 on failure
 */
int ced_server_client_finish(ced_server_client_p client) {
    if (client == NULL) {
        return CED_FAILURE;
    }

    if (client->server == NULL) {
        return CED_FAILURE;
    }

    close(client->fd);
    client->finished = 1;

    return CED_SUCCESS;
}

/**
 * @brief Closes all currently connected clients
 * @param server The server to close all clients on
 * @return 0 on success, -1 on failure
 */
int ced_server_close_all_clients(ced_server_p server) {
    if (server == NULL) {
        return CED_FAILURE;
    }

    if (server->clients == NULL) {
        return CED_FAILURE;
    }

    ced_list_node_p client_node;

    ced_list_foreach(client_node, server->clients) {
        ced_server_client_p client = (ced_server_client_p)client_node->data;
        close(client->fd);
    }

    return CED_SUCCESS;
}

/**
 * @brief Stops a server
 * @param server The server to stop
 * @return 0 on success, -1 on failure
 */
int ced_server_stop(ced_server_p server) {
    if (server == NULL) {
        return CED_FAILURE;
    }

    if (!server->running) {
        return CED_FAILURE;
    }

    if (server->fd != 0) {
        close(server->fd);
    }

    ced_server_close_all_clients(server);

    pthread_mutex_lock(&server->clients_mutex);
    ced_list_clear(server->clients);
    pthread_mutex_unlock(&server->clients_mutex);

    server->running = 0;

    return CED_SUCCESS;
}
