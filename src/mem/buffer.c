#include "buffer.h"

/**
 * @brief Creates a new buffer
 * @param size The size of the buffer
 * @return A pointer to the new buffer
 */
ced_buffer_p ced_buffer_new(size_t size) {
    if (size == 0 || (ssize_t)size < 0) {
        return NULL;
    }

    ced_buffer_p buffer = malloc(sizeof(ced_buffer_t));

    if (buffer == NULL) {
        return NULL;
    }

    ced_reflect_set_info(buffer, reflect_type_buffer);

    buffer->data = malloc(size);
    buffer->size = size;

    if (buffer->data == NULL) {
        free(buffer);
        return NULL;
    }

    memset(buffer->data, 0, buffer->size);
    buffer->size = size;

    return buffer;
}

/**
 * @brief Creates a new buffer
 * @param size The size of the buffer
 * @param data The data to copy into the buffer
 * @return A pointer to the new buffer
 */
ced_buffer_p ced_buffer_new_raw(size_t size, const void *data) {
    if (data == NULL || size == 0) {
        return NULL;
    }

    ced_buffer_p buffer = ced_buffer_new(size);

    if (buffer == NULL) {
        return NULL;
    }

    memcpy(buffer->data, data, size);
    return buffer;
}

/**
 * @brief Creates a new buffer
 * @param data The string to create a buffer from
 * @return A pointer to the new buffer
 */
ced_buffer_p ced_buffer_new_str(const char *data) {
    if (data == NULL) {
        return NULL;
    }

    size_t size = strlen(data);
    ced_buffer_p buffer = ced_buffer_new(size);

    if (buffer == NULL) {
        return NULL;
    }

    memcpy(buffer->data, data, size);
    return buffer;
}

/**
 * @brief Creates a new buffer from a file
 * @param path The path to the file
 * @return A pointer to the new buffer
 */
ced_buffer_p ced_buffer_new_file(const char *path) {
    if (path == NULL) {
        return NULL;
    }

    FILE *file = fopen(path, "rb");

    if (file == NULL) {
        return NULL;
    }

    // get the size of the file, to create a buffer
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);

    if (size == 0) {
        fclose(file);
        return NULL;
    }

    // rewind the file
    fseek(file, 0, SEEK_SET);

    ced_buffer_p buffer = ced_buffer_new(size);
    size_t size_read = fread(buffer->data, 1, size, file);
    fclose(file);

    if (size_read != size) {
        ced_buffer_free(buffer);
        return NULL;
    }

    return buffer;
}

/**
 * @Brief Creates a new buffer from the data at the file handle
 * @param handle The file handle
 * @param _chunk_size The size of the chunks to read
 * @return A pointer to the new buffer
 */
ced_buffer_p ced_buffer_new_handle(int handle, size_t _chunk_size) {
    size_t chunk_size = 4096;

    if (_chunk_size > 0) {
        chunk_size = _chunk_size;
    }

    if (handle < 0) {
        return NULL;
    }

    ced_buffer_p buffer = ced_buffer_new(chunk_size);

    ssize_t total_read = 0, bytes_read = 0;

    do {
        if (total_read + chunk_size > buffer->size) {
            // Expand the buffer if necessary
            if (ced_buffer_resize(buffer, buffer->size + chunk_size) != CED_SUCCESS) {
                ced_buffer_free(buffer);
                return NULL;
            }
        }

        bytes_read = read(handle, buffer->data + total_read, chunk_size);
        // bytes_read = recv(handle, buffer->data + total_read, chunk_size, MSG_DONTWAIT);
        if (bytes_read < 0) {
            ced_buffer_free(buffer);
            return NULL;
        }

        total_read += bytes_read;
    } while (bytes_read == chunk_size);

    if (total_read < buffer->size) {
        if (ced_buffer_resize(buffer, total_read) != CED_SUCCESS) {
            ced_buffer_free(buffer);
            return NULL;
        }
    }

    printf("Read %zd bytes\n", total_read);

    return buffer;
}


/**
 * @brief Creates a new buffer full of random data
 * @param size The size of the buffer
 * @return A pointer to the new buffer
 */
ced_buffer_p ced_buffer_new_random(size_t size) {
    if (size == 0) {
        return NULL;
    }

    ced_buffer_p buffer = ced_buffer_new(size);

    if (buffer == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; ++i) {
        ((unsigned char *)buffer->data)[i] = rand() % 256;
    }

    return buffer;
}

/**
 * @brief Frees a buffer
 * @param buffer The buffer to free
 */
void ced_buffer_free(ced_buffer_p buffer) {
    if (buffer == NULL) {
        return;
    }

    if (buffer->data != NULL) {
        free(buffer->data);
        buffer->data = NULL;
    }

    free(buffer);
}

/**
 * @brief Resizes a buffer
 * @param buffer The buffer to resize
 * @param size The new size of the buffer
 * @return 0 on success, -1 on failure
 */
int ced_buffer_resize(ced_buffer_p buffer, size_t size) {
    if (buffer == NULL || size == 0) {
        return CED_FAILURE;
    }

    if (buffer->data == NULL) {
        return CED_FAILURE;
    }

    // allocate the new data buffer
    void *new_data = malloc(size);

    if (new_data == NULL) {
        return CED_FAILURE;
    }

    size_t min_size = buffer->size < size ? buffer->size : size;

    // copy the old data into the new buffer
    memcpy(new_data, buffer->data, min_size);
    free(buffer->data);

    buffer->data = new_data;
    buffer->size = size;

    return CED_SUCCESS;
}

/**
 * @brief Compares two buffers
 * @param buffer1 The first buffer
 * @param buffer2 The second buffer
 * @return 0 if the buffers are equal, -1 if the first buffer is less than the second, 1 if the first buffer is greater than the second
 */
int ced_buffer_cmp(ced_buffer_p buffer1, ced_buffer_p buffer2) {
    if (buffer1 == NULL || buffer2 == NULL) {
        return -1;
    }

    if (buffer1->data == NULL || buffer2->data == NULL) {
        return -1;
    }

    // size based comparison
    if (buffer1->size < buffer2->size) {
        return -1;
    }

    // reverse view: size based comparison
    if (buffer1->size > buffer2->size) {
        return 1;
    }

    return memcmp(buffer1->data, buffer2->data, buffer1->size);
}

/**
 * @brief Compares the contents of a buffer to a string
 * @param buffer1 The first buffer
 * @param s The string to compare to
 * @return 0 if the buffers are equal, -1 if the first buffer is less than the second, 1 if the first buffer is greater than the second
 */
int ced_buffer_cmp_str(ced_buffer_p buffer1, const char *s) {
    if (buffer1 == NULL || s == NULL) {
        return -1;
    }

    if (buffer1->data == NULL) {
        return -1;
    }

    size_t slen = strlen(s);

    // size based comparison
    if (buffer1->size < slen) {
        return -1;
    }

    // reverse view: size based comparison
    if (buffer1->size > slen) {
        return 1;
    }

    return strncmp(buffer1->data, s, buffer1->size);
}

/**
 * @brief Duplicates a buffer
 * @param buffer The buffer to duplicate
 * @return A pointer to the new buffer
 */
ced_buffer_p ced_buffer_dup(ced_buffer_p buffer) {
    if (buffer == NULL || buffer->data == NULL) {
        return NULL;
    }

    ced_buffer_p new_buffer = ced_buffer_new(buffer->size);

    if (new_buffer == NULL) {
        return NULL;
    }

    memcpy(new_buffer->data, buffer->data, buffer->size);

    return new_buffer;
}

/**
 * @brief Fills a buffer with a character
 * @param buffer The buffer to fill
 * @param c The character to fill the buffer with
 * @return 0 on success, -1 on failure
 */
int ced_buffer_fill(ced_buffer_p buffer, int c) {
    if (buffer == NULL || buffer->data == NULL) {
        return CED_FAILURE;
    }

    memset(buffer->data, c, buffer->size);

    return CED_SUCCESS;
}

/**
 * @brief Copies data into a buffer
 * @param dest The buffer to copy into
 * @param src The buffer to copy from
 * @return 0 on success, -1 on failure
 */
int ced_buffer_copy(ced_buffer_p dest, ced_buffer_p src) {
    if (dest == NULL || src == NULL) {
        return CED_FAILURE;
    }

    if (dest->data == NULL || src->data == NULL) {
        return CED_FAILURE;
    }

    size_t min_size = dest->size < src->size ? dest->size : src->size;
    memcpy(dest->data, src->data, min_size);

    return CED_SUCCESS;
}

char *_ced_buffer_to_string_hex(ced_buffer_p buffer) {
    if (buffer == NULL || buffer->data == NULL || buffer->size == 0) {
        return NULL;
    }

    char *str = malloc(buffer->size * 2 + 1);

    if (str == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < buffer->size; ++i) {
        sprintf(str + i * 2, "%02x", ((unsigned char *)buffer->data)[i]);
    }

    str[buffer->size * 2] = '\0';

    return str;
}

char *_ced_buffer_to_string_base64(ced_buffer_p buffer) {
    if (buffer == NULL || buffer->data == NULL || buffer->size == 0) {
        return NULL;
    }

    return ced_base64_encode(buffer->data, buffer->size);
}

char *_ced_buffer_to_string_ascii(ced_buffer_p buffer) {
    if (buffer == NULL || buffer->data == NULL || buffer->size == 0) {
        return NULL;
    }

    char *str = (char*)malloc(buffer->size + 1);
    if (str == NULL) {
        return NULL;
    }

    memcpy(str, buffer->data, buffer->size);
    str[buffer->size] = '\0';

    return str;
}

/**
 * @brief Produces a string from a buffer
 * @param buffer The buffer to convert
 * @param encoding The encoding to use
 * @return A pointer to the new string
 */
char *ced_buffer_to_string(ced_buffer_p buffer, ced_encoding_t encoding) {
    if (buffer == NULL || buffer->data == NULL) {
        return NULL;
    }

    switch (encoding) {
        case ced_encoding_hex:
            return _ced_buffer_to_string_hex(buffer);
        case ced_encoding_base64:
            return _ced_buffer_to_string_base64(buffer);
        case ced_encoding_ascii:
            return _ced_buffer_to_string_ascii(buffer);
    }

    return NULL;
}
