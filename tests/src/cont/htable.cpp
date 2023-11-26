//
// Created by michael on 10/11/23.
//

#include "gtest/gtest.h"
#include "ced.h"

namespace {
    TEST(HashTableTests, Construction) {
        ced_htable_p htable = ced_htable_new(10);

        EXPECT_EQ(htable->size, 10);
        EXPECT_EQ(htable->count, 0);

        ced_htable_free(htable);
    }
    TEST(HashTableTests, InsertOneThing) {
        ced_htable_p htable = ced_htable_new(10);

        ced_htable_insert(htable, "key", (void *)1);

        EXPECT_EQ(htable->size, 10);
        EXPECT_EQ(htable->count, 1);

        ced_htable_free(htable);
    }
    TEST(HashTableTests, InsertFiveThings) {
        ced_htable_p htable = ced_htable_new(10);

        ced_htable_insert(htable, "key1", (void *)1);
        ced_htable_insert(htable, "key2", (void *)2);
        ced_htable_insert(htable, "key3", (void *)3);
        ced_htable_insert(htable, "key4", (void *)4);
        ced_htable_insert(htable, "key5", (void *)5);

        EXPECT_EQ(htable->size, 10);
        EXPECT_EQ(htable->count, 5);

        ced_htable_free(htable);
    }
    TEST(HashTableTests, InsertFiveThingsAndRetrieve) {
        ced_htable_p htable = ced_htable_new(10);

        ced_htable_insert(htable, "key1", (void *)1);
        ced_htable_insert(htable, "key2", (void *)2);
        ced_htable_insert(htable, "key3", (void *)3);
        ced_htable_insert(htable, "key4", (void *)4);
        ced_htable_insert(htable, "key5", (void *)5);

        EXPECT_EQ(htable->size, 10);
        EXPECT_EQ(htable->count, 5);

        EXPECT_EQ(ced_htable_get(htable, "key1"), (void *)1);
        EXPECT_EQ(ced_htable_get(htable, "key2"), (void *)2);
        EXPECT_EQ(ced_htable_get(htable, "key3"), (void *)3);
        EXPECT_EQ(ced_htable_get(htable, "key4"), (void *)4);
        EXPECT_EQ(ced_htable_get(htable, "key5"), (void *)5);

        ced_htable_free(htable);
    }
}