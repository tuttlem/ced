#ifndef __ced_net_server_h__

#define __ced_net_server_h__

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../defs.h"
#include "../reflect.h"
#include "../cont/list.h"
#include "../util/log.h"

typedef struct ced_server_t ced_server_t, *ced_server_p;

/**
 * @brief Describes a client
 */
typedef struct ced_server_client_t {
    CED_REFLECT_INFO

    int fd;                 /* The file descriptor of the client */
    char *host;             /* The host of the client */
    int port;               /* The port of the client */
    ced_server_p server;    /* The server the client is connected to */
} ced_server_client_t, *ced_server_client_p;

typedef void(*ced_server_handler)(ced_server_client_p client);

/**
 * @brief Describes a server
 */
typedef struct ced_server_t {
    CED_REFLECT_INFO

    int fd;                     /* The file descriptor of the server */
    char *host;                 /* The host to bind to */
    int port;                   /* The port to bind to */
    int running;                /* Whether or not the server is running */

    ced_list_p clients;         /* The clients connected to the server */
    ced_server_handler handler; /* Handler function for client connections */
} ced_server_t, *ced_server_p;

/**
 * @brief Creates a new server
 * @param host The host to bind to
 * @param port The port to bind to
 * @param handler The handler function for client connections
 * @return A pointer to the new server
 */
ced_server_p ced_server_new(const char *host, int port, ced_server_handler handler);

/**
 * @brief Frees a server
 * @param server The server to free
 */
void ced_server_free(ced_server_p server);

/**
 * @brief Creates a new client
 * @param fd The file descriptor of the client
 * @param host The connecting client
 * @param port The port of the client
 * @return A pointer to the new client
 */
ced_server_client_p ced_server_client_new(int fd, const char *host, int port);

/**
 * @brief Frees a client
 * @param client The client to free
 */
void ced_server_client_free(ced_server_client_p client);

/**
 * @brief Starts a server
 * @param server The server to start
 * @return 0 on success, -1 on failure
 */
int ced_server_start(ced_server_p server);

/**
 * @brief Finishes a client connection
 * @param client The client to finish
 * @return 0 on success, -1 on failure
 */
int ced_server_client_finish(ced_server_client_p client);

/**
 * @brief Closes all currently connected clients
 * @param server The server to close all clients on
 * @return 0 on success, -1 on failure
 */
int ced_server_close_all_clients(ced_server_p server);

/**
 * @brief Stops a server
 * @param server The server to stop
 * @return 0 on success, -1 on failure
 */
int ced_server_stop(ced_server_p server);

#endif /* __ced_net_server_h__ */