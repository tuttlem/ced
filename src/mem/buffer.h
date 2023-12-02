#ifndef __ced_mem_buffer_h__
#define __ced_mem_buffer_h__

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "../defs.h"
#include "../reflect.h"
#include "../util/base64.h"

typedef struct {
    CED_REFLECT_INFO

    void *data;
    size_t size;
} ced_buffer_t, *ced_buffer_p;

/**
 * @brief Creates a new buffer
 * @param size The size of the buffer
 * @return A pointer to the new buffer
 */
ced_buffer_p ced_buffer_new(size_t size);

/**
 * @brief Creates a new buffer
 * @param size The size of the buffer
 * @param data The data to copy into the buffer
 * @return A pointer to the new buffer
 */
ced_buffer_p ced_buffer_new_raw(size_t size, const void *data);

/**
 * @brief Creates a new buffer
 * @param data The string to create a buffer from
 * @return A pointer to the new buffer
 */
ced_buffer_p ced_buffer_new_str(const char *data);

/**
 * @brief Creates a new buffer from a file
 * @param path The path to the file
 * @return A pointer to the new buffer
 */
ced_buffer_p ced_buffer_new_file(const char *path);

/**
 * @Brief Creates a new buffer from the data at the file handle
 * @param handle The file handle
 * @return A pointer to the new buffer
 */
ced_buffer_p ced_buffer_new_handle(int handle);

/**
 * @brief Creates a new buffer full of random data
 * @param size The size of the buffer
 * @return A pointer to the new buffer
 */
ced_buffer_p ced_buffer_new_random(size_t size);

/**
 * @brief Frees a buffer
 * @param buffer The buffer to free
 */
void ced_buffer_free(ced_buffer_p buffer);

/**
 * @brief Resizes a buffer
 * @param buffer The buffer to resize
 * @param size The new size of the buffer
 * @return 0 on success, -1 on failure
 */
int ced_buffer_resize(ced_buffer_p buffer, size_t size);

/**
 * @brief Compares two buffers
 * @param buffer1 The first buffer
 * @param buffer2 The second buffer
 * @return 0 if the buffers are equal, -1 if the first buffer is less than the second, 1 if the first buffer is greater than the second
 */
int ced_buffer_cmp(ced_buffer_p buffer1, ced_buffer_p buffer2);

/**
 * @brief Duplicates a buffer
 * @param buffer The buffer to duplicate
 * @return A pointer to the new buffer
 */
ced_buffer_p ced_buffer_dup(ced_buffer_p buffer);

/**
 * @brief Fills a buffer with a character
 * @param buffer The buffer to fill
 * @param c The character to fill the buffer with
 * @return 0 on success, -1 on failure
 */
int ced_buffer_fill(ced_buffer_p buffer, int c);

/**
 * @brief Copies data into a buffer
 * @param dest The buffer to copy into
 * @param src The buffer to copy from
 * @return 0 on success, -1 on failure
 */
int ced_buffer_copy(ced_buffer_p dest, ced_buffer_p src);

/**
 * @brief Produces a string from a buffer
 * @param buffer The buffer to convert
 * @param encoding The encoding to use
 * @return A pointer to the new string
 */
char *ced_buffer_to_string(ced_buffer_p buffer, ced_encoding_t encoding);

#endif /* __ced_mem_buffer_h__ */