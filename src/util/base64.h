#ifndef __ced_util_base64_h__
#define __ced_util_base64_h__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../defs.h"

/**
 * @brief Encodes data into base64
 * @param data The data to encode
 * @param input_length The length of the data to encode
 * @return A pointer to the encoded data
 */
char* ced_base64_encode(const unsigned char* data, size_t input_length);

/**
 * @brief Decodes base64 data
 * @param data The data to decode
 * @param input_length The length of the data to decode
 * @param decoded_data A pointer to the decoded data
 * @param decoded_length A pointer to the length of the decoded data
 * @return
 */
int ced_base64_decode(const char* data, size_t input_length, unsigned char** decoded_data, size_t* decoded_length);

#endif /* __ced_util_base64_h__ */