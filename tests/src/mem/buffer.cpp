//
// Created by michael on 10/11/23.
//

#include "gtest/gtest.h"
#include "ced.h"

namespace {
    TEST(BufferTests, ConstructWithSize) {
        ced_buffer_p buffer = ced_buffer_new(256);
        EXPECT_EQ(buffer->size, 256);
        ced_buffer_free(buffer);
    }
    TEST(BufferTests, ConstructWithNegativeSize) {
        ced_buffer_p buffer = ced_buffer_new(-1);
        EXPECT_TRUE(buffer == NULL);
    }

    TEST(BufferTests, ConstructWithZero) {
        ced_buffer_p buffer = ced_buffer_new(0);
        EXPECT_TRUE(buffer == NULL);
    }
    TEST(BufferTests, ConstructWithSizeAndData) {
        char *data = "Hello, World!";
        ced_buffer_p buffer = ced_buffer_new_data(256, data);
        EXPECT_EQ(buffer->size, 256);
        EXPECT_TRUE(memcmp(buffer->data, data, 256) == 0);

        ced_buffer_free(buffer);
    }
    TEST(BufferTests, ResizeHigher) {
        ced_buffer_p buffer = ced_buffer_new_data(256, "Hello, World!");
        EXPECT_EQ(buffer->size, 256);
        int status = ced_buffer_resize(buffer, 512);
        EXPECT_EQ(status, 0);
        EXPECT_EQ(buffer->size, 512);
        EXPECT_TRUE(memcmp(buffer->data, "Hello, World!", 13) == 0);
        ced_buffer_free(buffer);
    }
    TEST(BufferTests, ResizeLower) {
        ced_buffer_p buffer = ced_buffer_new_data(256, "Hello, World!");
        EXPECT_EQ(buffer->size, 256);
        int status = ced_buffer_resize(buffer, 5);
        EXPECT_EQ(status, 0);
        EXPECT_EQ(buffer->size, 5);
        EXPECT_TRUE(memcmp(buffer->data, "Hello", 5) == 0);
        ced_buffer_free(buffer);
    }
    TEST(BufferTests, ResizeToZero) {
        ced_buffer_p buffer = ced_buffer_new_data(256, "Hello, World!");
        EXPECT_EQ(buffer->size, 256);
        int status = ced_buffer_resize(buffer, 0);
        EXPECT_EQ(status, -1);
        ced_buffer_free(buffer);
    }
    TEST(BufferTests, Compare) {
        ced_buffer_p buffer = ced_buffer_new_data(256, "Hello, World!");
        EXPECT_EQ(buffer->size, 256);
        ced_buffer_p buffer2 = ced_buffer_new_data(256, "Hello, World!");
        EXPECT_EQ(buffer2->size, 256);
        EXPECT_EQ(ced_buffer_cmp(buffer, buffer2), 0);
        ced_buffer_free(buffer);
        ced_buffer_free(buffer2);
    }
    TEST(BufferTests, CompareDifferent) {
        ced_buffer_p buffer = ced_buffer_new_data(256, "Hello, World!");
        EXPECT_EQ(buffer->size, 256);
        ced_buffer_p buffer2 = ced_buffer_new_data(256, "Hello, World");
        EXPECT_EQ(buffer2->size, 256);
        EXPECT_TRUE(ced_buffer_cmp(buffer, buffer2) > 0);
        ced_buffer_free(buffer);
        ced_buffer_free(buffer2);
    }
    TEST(BufferTests, CompareDifferentSize) {
        ced_buffer_p buffer = ced_buffer_new_data(256, "Hello, World!");
        EXPECT_EQ(buffer->size, 256);
        ced_buffer_p buffer2 = ced_buffer_new_data(512, "Hello, World!");
        EXPECT_EQ(buffer2->size, 512);
        EXPECT_EQ(ced_buffer_cmp(buffer, buffer2), -1);
        ced_buffer_free(buffer);
        ced_buffer_free(buffer2);
    }
    TEST(BufferTests, CompareNull) {
        ced_buffer_p buffer = ced_buffer_new_data(256, "Hello, World!");
        EXPECT_EQ(buffer->size, 256);
        EXPECT_EQ(ced_buffer_cmp(buffer, NULL), -1);
        ced_buffer_free(buffer);
    }
    TEST(BufferTests, Duplicate) {
        ced_buffer_p buffer = ced_buffer_new_data(256, "Hello, World!");
        EXPECT_EQ(buffer->size, 256);
        ced_buffer_p buffer2 = ced_buffer_dup(buffer);
        EXPECT_EQ(buffer2->size, 256);
        EXPECT_EQ(ced_buffer_cmp(buffer, buffer2), 0);
        ced_buffer_free(buffer);
        ced_buffer_free(buffer2);
    }
    TEST(BufferTests, DuplicateNull) {
        ced_buffer_p buffer = ced_buffer_dup(NULL);
        EXPECT_TRUE(buffer == NULL);
    }
    TEST(BufferTests, Fill) {
        unsigned char ones[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        ced_buffer_p buffer = ced_buffer_new(10);
        EXPECT_EQ(buffer->size, 10);
        int status = ced_buffer_fill(buffer, 1);
        EXPECT_EQ(status, 0);
        unsigned char *buffer_data = (unsigned char*)buffer->data;
        // EXPECT_TRUE(memcmp(buffer_data, ones, 10) == 0);
        EXPECT_EQ(buffer_data[0], ones[0]);
        ced_buffer_free(buffer);
    }
}