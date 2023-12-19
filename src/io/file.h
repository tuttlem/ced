#ifndef __ced_io_file_h__
#define __ced_io_file_h__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../mem/buffer.h"

/**
 * @brief Reads a file into a buffer
 * @param path The path to the file
 * @return A pointer to the buffer
 */
const char *ced_fgets(const char *path);

/**
 * @brief Reads a file into a buffer
 * @param path The path to the file
 * @return A pointer to the buffer
 */
ced_buffer_p ced_fget(const char *path);

/**
 * @brief Writes data to a file
 * @param path The path to the file
 * @param data The data to write
 * @return The number of bytes written
 */
int ced_fputs(const char *path, const char *data);

/**
 * @brief Appends data to a file
 * @param path The path to the file
 * @param data The data to append
 * @return The number of bytes written
 */
int ced_fappends(const char *path, const char *data);

/**
 * @brief Writes a buffer to a file
 * @param path The path to the file
 * @param buffer The buffer to write
 * @return The number of bytes written
 */
int ced_fput(const char *path, ced_buffer_p buffer);

#endif /* __ced_io_file_h__ */