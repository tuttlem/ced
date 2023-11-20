//
// Created by michael on 10/11/23.
//

#include "gtest/gtest.h"
#include "ced.h"

namespace {
    TEST(QueueTests, Construction) {
        ced_queue_p queue = ced_queue_new();
        EXPECT_EQ(queue->size, 0);
        ced_queue_free(queue);
    }

    TEST(QueueTests, EnqueueFiveThings) {
        ced_queue_p queue = ced_queue_new();

        ced_queue_enqueue(queue, (void *)1);
        ced_queue_enqueue(queue, (void *)2);
        ced_queue_enqueue(queue, (void *)3);
        ced_queue_enqueue(queue, (void *)4);
        ced_queue_enqueue(queue, (void *)5);

        EXPECT_EQ(queue->size, 5);

        ced_queue_free(queue);
    }

    TEST(QueueTests, DequeueFiveThings) {
        ced_queue_p queue = ced_queue_new();

        ced_queue_enqueue(queue, (void *)1);
        ced_queue_enqueue(queue, (void *)2);
        ced_queue_enqueue(queue, (void *)3);
        ced_queue_enqueue(queue, (void *)4);
        ced_queue_enqueue(queue, (void *)5);

        unsigned int i = 1;

        while (queue->size > 0) {
            EXPECT_EQ(ced_queue_dequeue(queue), (void *)i);
            i++;
        }

        EXPECT_EQ(queue->size, 0);

        ced_queue_free(queue);
    }
}