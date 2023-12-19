#include "file.h"

/**
 * @brief Reads a file into a buffer
 * @param path The path to the file
 * @return A pointer to the buffer
 */
const char *ced_fgets(const char *path) {
    ced_buffer_p buffer = ced_fget(path);

    if (buffer == NULL) {
        return NULL;
    }

    char *data = malloc(buffer->size + 1);
    memcpy(data, buffer->data, buffer->size);
    data[buffer->size] = '\0';

    ced_buffer_free(buffer);
    return data;
}

/**
 * @brief Reads a file into a buffer
 * @param path The path to the file
 * @return A pointer to the buffer
 */
ced_buffer_p ced_fget(const char *path) {
    if (path == NULL) {
        return NULL;
    }

    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        return NULL;
    }

    ced_buffer_p buffer = ced_buffer_new_handle(fd, 1024);
    close(fd);
    return buffer;
}

/**
 * @brief Writes data to a file
 * @param path The path to the file
 * @param data The data to write
 * @return The number of bytes written
 */
int ced_fputs(const char *path, const char *data) {
    if (path == NULL || data == NULL) {
        return -1;
    }

    int fd = open(path, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        return -1;
    }

    int bytes_written = write(fd, data, strlen(data));
    close(fd);
    return bytes_written;
}

/**
 * @brief Appends data to a file
 * @param path The path to the file
 * @param data The data to append
 * @return The number of bytes written
 */
int ced_fappends(const char *path, const char *data) {
    if (path == NULL || data == NULL) {
        return -1;
    }

    int fd = open(path, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        return -1;
    }

    int bytes_written = write(fd, data, strlen(data));
    close(fd);
    return bytes_written;
}

/**
 * @brief Writes a buffer to a file
 * @param path The path to the file
 * @param buffer The buffer to write
 * @return The number of bytes written
 */
int ced_fput(const char *path, ced_buffer_p buffer) {
    if (path == NULL || buffer == NULL) {
        return -1;
    }

    int fd = open(path, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        return -1;
    }

    int bytes_written = write(fd, buffer->data, buffer->size);
    close(fd);
    return bytes_written;
}
