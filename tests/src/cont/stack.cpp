//
// Created by michael on 10/11/23.
//

#include "gtest/gtest.h"
#include "ced.h"

namespace {
    TEST(StackTests, Construction) {
        ced_stack_p stack = ced_stack_new();
        EXPECT_EQ(ced_stack_size(stack), 0);
        ced_stack_free(stack);
    }

    TEST(StackTests, PushFiveThings) {
        ced_stack_p stack = ced_stack_new();

        ced_stack_push(stack, (void *)1);
        ced_stack_push(stack, (void *)2);
        ced_stack_push(stack, (void *)3);
        ced_stack_push(stack, (void *)4);
        ced_stack_push(stack, (void *)5);

        EXPECT_EQ(ced_stack_size(stack), 5);

        ced_stack_free(stack);
    }

    TEST(StackTests, PushPopFiveThings) {
        ced_stack_p stack = ced_stack_new();

        ced_stack_push(stack, (void *)1);
        ced_stack_push(stack, (void *)2);
        ced_stack_push(stack, (void *)3);
        ced_stack_push(stack, (void *)4);
        ced_stack_push(stack, (void *)5);

        unsigned int i = 5;

        while (ced_stack_size(stack) > 0) {
            EXPECT_EQ(ced_stack_size(stack), i);
            EXPECT_EQ(ced_stack_pop(stack), (void *)i);
            i--;
        }

        EXPECT_EQ(ced_stack_size(stack), 0);

        ced_stack_free(stack);
    }
}