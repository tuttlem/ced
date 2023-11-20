//
// Created by michael on 10/11/23.
//

#include "gtest/gtest.h"
#include "ced.h"

namespace {
    TEST(BTreeTests, Construction) {
        ced_btree_p btree = ced_btree_new(NULL);
        EXPECT_EQ(btree->size, 0);
        ced_btree_free(btree);
    }

    TEST(BTreeTests, AddFiveThings) {
        ced_btree_p btree = ced_btree_new(NULL);

        ced_btree_insert(btree, (void *)1, (void *)1);
        ced_btree_insert(btree, (void *)2, (void *)2);
        ced_btree_insert(btree, (void *)3, (void *)3);
        ced_btree_insert(btree, (void *)4, (void *)4);
        ced_btree_insert(btree, (void *)5, (void *)5);

        EXPECT_EQ(btree->size, 5);

        ced_btree_free(btree);
    }

    TEST(BTreeTests, GetTheThree) {
        ced_btree_p btree = ced_btree_new(NULL);

        ced_btree_insert(btree, (void *)1, (void *)1);
        ced_btree_insert(btree, (void *)2, (void *)2);
        ced_btree_insert(btree, (void *)3, (void *)3);
        ced_btree_insert(btree, (void *)4, (void *)4);
        ced_btree_insert(btree, (void *)5, (void *)5);

        EXPECT_EQ(ced_btree_get(btree, (void *)3), (void *)3);

        ced_btree_free(btree);
    }
}