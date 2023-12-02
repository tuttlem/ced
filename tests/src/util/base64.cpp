//
// Created by michael on 10/11/23.
//

#include "gtest/gtest.h"
#include "ced.h"

namespace {
    TEST(Base64Tests, EncodeNull) {
        char *encoded = ced_base64_encode(NULL, 0);
        EXPECT_TRUE(encoded == NULL);
    }
    TEST(Base64Tests, EncodeEmpty) {
        unsigned char in[] = { };
        char *encoded = ced_base64_encode(in, 0);
        EXPECT_TRUE(encoded == NULL);
    }
    TEST(Base64Tests, EncodeHello) {
        unsigned char in[] = { 'h', 'e', 'l', 'l', 'o' };
        char *encoded = ced_base64_encode(in, 5);
        EXPECT_STREQ(encoded, "aGVsbG8=");
        free(encoded);
    }
    TEST(Base64Tests, DecodeNull) {
        unsigned char *decoded;
        size_t decoded_len;
        int result = ced_base64_decode(NULL, 0, &decoded, &decoded_len);
        EXPECT_EQ(result, CED_FAILURE);
        EXPECT_TRUE(decoded == NULL);
    }
    TEST(Base64Tests, DecodeEmpty) {
        char *in = "";
        unsigned char *decoded;
        size_t decoded_len;
        int result = ced_base64_decode(in, 0, &decoded, &decoded_len);
        EXPECT_EQ(result, CED_FAILURE);
        EXPECT_TRUE(decoded == NULL);
    }
    TEST(Base64Tests, DecodeHello) {
        char *in = "aGVsbG8=";
        unsigned char *decoded;
        size_t decoded_len;
        int result = ced_base64_decode(in, strlen(in), &decoded, &decoded_len);
        EXPECT_EQ(result, CED_SUCCESS);
        EXPECT_EQ(decoded_len, 5);
        EXPECT_EQ(decoded[0], (unsigned char)0x68); // h
        EXPECT_EQ(decoded[1], (unsigned char)0x65); // e
        EXPECT_EQ(decoded[2], (unsigned char)0x6c); // l
        EXPECT_EQ(decoded[3], (unsigned char)0x6c); // l
        EXPECT_EQ(decoded[4], (unsigned char)0x6f); // o
        free(decoded);
    }
}