
#include "base64.h"

const char _ced_base64_table_enc[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K' ,'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S' ,'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', 'a' ,'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i' ,'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q' ,'r', 's', 't', 'u', 'v',
        'w', 'x', 'y' ,'z', '0', '1', '2', '3',
        '4', '5', '6' ,'7', '8', '9', '+', '/'
};

const char _ced_base64_table_dec[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 62, 0, 0, 0, 63,
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 0, 0, 0, 0,
        0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
/**
 * @brief Encodes data into base64
 * @param data The data to encode
 * @param input_length The length of the data to encode
 * @return A pointer to the encoded data
 */
char* ced_base64_encode(const unsigned char* data, size_t input_length) {
    if (data == NULL || input_length == 0) {
        return NULL;
    }

    // Calculate the output buffer length
    size_t output_length = 4 * ((input_length + 2) / 3);

    // +1 for null terminator
    char* encoded_data = (char*)malloc(output_length + 1);

    if (encoded_data == NULL) {
        return NULL;
    }

    size_t i, j;
    for (i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;

        encoded_data[j++] = _ced_base64_table_enc[(triple >> 18) & 0x3F];
        encoded_data[j++] = _ced_base64_table_enc[(triple >> 12) & 0x3F];
        encoded_data[j++] = _ced_base64_table_enc[(triple >> 6) & 0x3F];
        encoded_data[j++] = _ced_base64_table_enc[triple & 0x3F];
    }

    // Pad the last group if necessary
    for (i = 0; i < (3 - input_length % 3) % 3; i++) {
        encoded_data[output_length - 1 - i] = '=';
    }

    // Null-terminate the string
    encoded_data[output_length] = '\0';
    return encoded_data;
}


/**
 * @brief Decodes base64 data
 * @param data The data to decode
 * @param input_length The length of the data to decode
 * @param decoded_data A pointer to the decoded data
 * @param decoded_length A pointer to the length of the decoded data
 * @return
 */
int ced_base64_decode(const char* encoded_data, size_t input_length, unsigned char** decoded_data, size_t* output_length) {
    if (encoded_data == NULL || input_length == 0) {
        *decoded_data = NULL;
        *output_length = 0;
        return CED_FAILURE;
    }

    if (input_length % 4 != 0) {
        return CED_FAILURE;
    }

    *output_length = input_length / 4 * 3;
    if (encoded_data[input_length - 1] == '=') {
        (*output_length)--;
    }
    if (encoded_data[input_length - 2] == '=') {
        (*output_length)--;
    }

    *decoded_data = (unsigned char*)malloc(*output_length + 1);
    if (*decoded_data == NULL) {
        return CED_FAILURE;
    }

    size_t i, j;
    for (i = 0, j = 0; i < input_length;) {
        uint32_t sextet_a = (uint32_t) (encoded_data[i] == '=' ? 0 & i++ : _ced_base64_table_dec[(size_t) encoded_data[i++]]);
        uint32_t sextet_b = (uint32_t) (encoded_data[i] == '=' ? 0 & i++ : _ced_base64_table_dec[(size_t)encoded_data[i++]]);
        uint32_t sextet_c = (uint32_t) (encoded_data[i] == '=' ? 0 & i++ : _ced_base64_table_dec[(size_t)encoded_data[i++]]);
        uint32_t sextet_d = (uint32_t) (encoded_data[i] == '=' ? 0 & i++ : _ced_base64_table_dec[(size_t)encoded_data[i++]]);

        if ((sextet_a | sextet_b | sextet_c | sextet_d) & 0x80000000) {
            free(*decoded_data);
            return CED_FAILURE;
        }

        uint32_t triple = (sextet_a << 18) | (sextet_b << 12) | (sextet_c << 6) | sextet_d;

        if (j < *output_length) {
            (*decoded_data)[j++] = (triple >> 16) & 0xFF;
        }
        if (j < *output_length) {
            (*decoded_data)[j++] = (triple >> 8) & 0xFF;
        }
        if (j < *output_length) {
            (*decoded_data)[j++] = triple & 0xFF;
        }
    }

    (*decoded_data)[j] = '\0'; // Null-terminate the decoded data

    return CED_SUCCESS;
}
