//
// Created by michael on 10/11/23.
//

#include "gtest/gtest.h"
#include "ced.h"

namespace {
    TEST(ListTests, Construction) {
        ced_list_p list = ced_list_new();
        EXPECT_EQ(list->size, 0);
        ced_list_free(list);
    }
    TEST(ListTests, AppendFiveThings) {
        ced_list_p list = ced_list_new();

        ced_list_append(list, (void *)1);
        ced_list_append(list, (void *)2);
        ced_list_append(list, (void *)3);
        ced_list_append(list, (void *)4);
        ced_list_append(list, (void *)5);

        EXPECT_EQ(list->size, 5);

        ced_list_free(list);
    }
    TEST(ListTests, PrependSevenThings) {
        ced_list_p list = ced_list_new();

        ced_list_prepend(list, (void *)1);
        ced_list_prepend(list, (void *)2);
        ced_list_prepend(list, (void *)3);
        ced_list_prepend(list, (void *)4);
        ced_list_prepend(list, (void *)5);
        ced_list_prepend(list, (void *)6);
        ced_list_prepend(list, (void *)7);

        EXPECT_EQ(list->size, 7);

        ced_list_free(list);
    }
    TEST(ListTests, FindTheThree) {
        ced_list_p list = ced_list_new();

        ced_list_append(list, (void *)1);
        ced_list_append(list, (void *)2);
        ced_list_append(list, (void *)3);
        ced_list_append(list, (void *)4);
        ced_list_append(list, (void *)5);

        ced_list_node_p the_three = ced_list_find(list, NULL, (void *)3);
        EXPECT_EQ(the_three->data, (void *)3);

        ced_list_free(list);
    }
    TEST(ListTests, RemoveTheThree) {
        ced_list_p list = ced_list_new();

        ced_list_append(list, (void *)1);
        ced_list_append(list, (void *)2);
        ced_list_append(list, (void *)3);
        ced_list_append(list, (void *)4);
        ced_list_append(list, (void *)5);

        ced_list_remove(list, NULL, (void *)3);

        ced_list_node_p the_three = ced_list_find(list, NULL, (void *)3);
        EXPECT_EQ(the_three, (void*)NULL);

        EXPECT_EQ(list->size, 4);

        ced_list_free(list);
    }
    TEST(ListTests, FindTheName) {
        ced_list_p list = ced_list_new();

        ced_list_append(list, (void *)"Michael");
        ced_list_append(list, (void *)"John");
        ced_list_append(list, (void *)"Bob");
        ced_list_append(list, (void *)"Sally");
        ced_list_append(list, (void *)"Jane");

        ced_list_node_p the_name = ced_list_find(list, ced_data_cmp_str, (void *)"Bob");
        EXPECT_EQ(the_name->data, (void *)"Bob");

        ced_list_free(list);
    }
    TEST(ListTests, EnumeratesForward) {
        ced_list_p list = ced_list_new();

        ced_list_append(list, (void *)1);
        ced_list_append(list, (void *)2);
        ced_list_append(list, (void *)3);
        ced_list_append(list, (void *)4);
        ced_list_append(list, (void *)5);

        int i = 1;
        ced_list_node_p node;
        ced_list_foreach(node, list) {
            EXPECT_EQ(node->data, (void *)i);
            i++;
        }

        ced_list_free(list);
    }
    TEST(ListTests, EnumeratesInReverse) {
        ced_list_p list = ced_list_new();

        ced_list_append(list, (void *)1);
        ced_list_append(list, (void *)2);
        ced_list_append(list, (void *)3);
        ced_list_append(list, (void *)4);
        ced_list_append(list, (void *)5);

        int i = 5;
        ced_list_node_p node;
        ced_list_foreach_reverse(node, list) {
            EXPECT_EQ(node->data, (void *)i);
            i--;
        }

        ced_list_free(list);
    }
    TEST(ListTests, HeadAndRest) {
        ced_list_p list = ced_list_new();

        ced_list_append(list, (void *)1);
        ced_list_append(list, (void *)2);
        ced_list_append(list, (void *)3);
        ced_list_append(list, (void *)4);
        ced_list_append(list, (void *)5);

        void *head;
        ced_list_p rest;
        ced_list_head(list, &head, &rest);

        EXPECT_EQ(head, (void *)1);
        EXPECT_EQ(rest->size, 4);

        ced_list_free(rest);
    }
    TEST(ListTests, EnumerateWithHeadAndRest) {
        ced_list_p list = ced_list_new();

        int i = 1;

        for (i = 1; i < 1000000; i++) {
            ced_list_append(list, (void *)i);
        }

        i = 1;
        while (list->size > 0) {
            void *head;
            ced_list_p rest;
            ced_list_head(list, &head, &rest);

            EXPECT_EQ(head, (void *)i);
            EXPECT_EQ(rest->size, list->size - 1);

            // ced_list_free(list);
            list = rest;
            i++;
        }

        ced_list_free(list);
    }
    TEST(ListTests, GetSecondElement) {
        ced_list_p list = ced_list_new();
        ced_list_append(list, (void*)1);
        ced_list_append(list, (void*)2);
        ced_list_append(list, (void*)3);

        void *value = ced_list_get(list, 1);
        EXPECT_EQ(value, (void *) 2);

        ced_list_free(list);
    }
    TEST(ListTests, SetSecondElement) {
        ced_list_p list = ced_list_new();
        ced_list_append(list, (void*)1);
        ced_list_append(list, (void*)2);
        ced_list_append(list, (void*)3);

        ced_list_set(list, 1, (void*)5);
        void *value = ced_list_get(list, 1);
        EXPECT_EQ(value, (void *) 5);

        ced_list_free(list);
    }
    TEST(ListTests, InsertA5BeforeThe1Item) {
        ced_list_p list = ced_list_new();
        ced_list_append(list, (void*)1);
        ced_list_append(list, (void*)2);
        ced_list_append(list, (void*)3);

        ced_list_insert_before(list, 1, (void *)5);

        void *value = ced_list_get(list, 1);
        EXPECT_EQ(value, (void *) 5);
        value = ced_list_get(list, 2);
        EXPECT_EQ(value, (void *) 2);
        EXPECT_EQ(list->size, 4);

        ced_list_free(list);
    }
    TEST(ListTests, InsertA5AfterThe1Item) {
        ced_list_p list = ced_list_new();

        ced_list_append(list, (void*)1);
        ced_list_append(list, (void*)2);
        ced_list_append(list, (void*)3);

        ced_list_insert_after(list, 1, (void *)5);

        void *value = ced_list_get(list, 2);
        EXPECT_EQ(value, (void *) 5);
        value = ced_list_get(list, 3);
        EXPECT_EQ(value, (void *) 3);
        EXPECT_EQ(list->size, 4);

        ced_list_free(list);
    }
    TEST(ListTests, SortsValues) {
        ced_list_p list = ced_list_new();

        ced_list_append(list, (void*)5);
        ced_list_append(list, (void*)3);
        ced_list_append(list, (void*)1);
        ced_list_append(list, (void*)4);
        ced_list_append(list, (void*)2);

        ced_list_sort(list, NULL);

        void *value = ced_list_get(list, 0);
        EXPECT_EQ(value, (void *) 1);
        value = ced_list_get(list, 1);
        EXPECT_EQ(value, (void *) 2);
        value = ced_list_get(list, 2);
        EXPECT_EQ(value, (void *) 3);
        value = ced_list_get(list, 3);
        EXPECT_EQ(value, (void *) 4);
        value = ced_list_get(list, 4);
        EXPECT_EQ(value, (void *) 5);

        ced_list_free(list);
    }
}