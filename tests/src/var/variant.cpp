//
// Created by michael on 10/11/23.
//

#include "gtest/gtest.h"
#include "ced.h"

namespace {
    TEST(VariantTests, ConstructInt8) {
        ced_var_p var = ced_var_new_int8(1);

        EXPECT_EQ(var->__info.type, reflect_type_variant);
        EXPECT_EQ(var->type, ced_var_type_int8);
        EXPECT_EQ(var->data._int8, 1);
        ced_var_free(var);
    }

    TEST(VariantTests, ConstructInt16) {
        ced_var_p var = ced_var_new_int16(1);

        EXPECT_EQ(var->__info.type, reflect_type_variant);
        EXPECT_EQ(var->type, ced_var_type_int16);
        EXPECT_EQ(var->data._int16, 1);
        ced_var_free(var);
    }

    TEST(VariantTests, ConstructInt32) {
        ced_var_p var = ced_var_new_int32(1);
        EXPECT_EQ(var->type, ced_var_type_int32);
        EXPECT_EQ(var->data._int32, 1);
        ced_var_free(var);
    }

    TEST(VariantTests, ConstructInt64) {
        ced_var_p var = ced_var_new_int64(1);
        EXPECT_EQ(var->type, ced_var_type_int64);
        EXPECT_EQ(var->data._int64, 1);
        ced_var_free(var);
    }

    TEST(VariantTests, ConstructUInt8) {
        ced_var_p var = ced_var_new_uint8(1);
        EXPECT_EQ(var->type, ced_var_type_uint8);
        EXPECT_EQ(var->data._uint8, 1);
        ced_var_free(var);
    }

    TEST(VariantTests, ConstructUInt16) {
        ced_var_p var = ced_var_new_uint16(1);
        EXPECT_EQ(var->type, ced_var_type_uint16);
        EXPECT_EQ(var->data._uint16, 1);
        ced_var_free(var);
    }

    TEST(VariantTests, ConstructUInt32) {
        ced_var_p var = ced_var_new_uint32(1);
        EXPECT_EQ(var->type, ced_var_type_uint32);
        EXPECT_EQ(var->data._uint32, 1);
        ced_var_free(var);
    }

    TEST(VariantTests, ConstructUInt64) {
        ced_var_p var = ced_var_new_uint64(1);
        EXPECT_EQ(var->type, ced_var_type_uint64);
        EXPECT_EQ(var->data._uint64, 1);
        ced_var_free(var);
    }

    TEST(VariantTests, ConstructBool) {
        ced_var_p var = ced_var_new_bool(true);
        EXPECT_EQ(var->type, ced_var_type_bool);
        EXPECT_EQ(var->data._bool, true);
        ced_var_free(var);
    }

    TEST(VariantTests, ConstructFloat) {
        ced_var_p var = ced_var_new_float(1.0f);
        EXPECT_EQ(var->type, ced_var_type_float);
        EXPECT_EQ(var->data._float, 1.0f);
        ced_var_free(var);
    }

    TEST(VariantTests, ConstructDouble) {
        ced_var_p var = ced_var_new_double(1.0);
        EXPECT_EQ(var->type, ced_var_type_double);
        EXPECT_EQ(var->data._double, 1.0);
        ced_var_free(var);
    }

    TEST(VariantTests, ConstructString) {
        ced_var_p var = ced_var_new_string("test");
        EXPECT_EQ(var->type, ced_var_type_string);
        EXPECT_STREQ(var->data._string, "test");

        ced_var_free(var);
    }

    TEST(VariantTests, ConstructPointer) {
        ced_var_p var = ced_var_new_pointer((void *)0xdeadbeef);
        EXPECT_EQ(var->type, ced_var_type_pointer);
        EXPECT_EQ(var->data._pointer, (void *)0xdeadbeef);

        // prevents inner-free
        var->data._pointer = NULL;
        ced_var_free(var);
    }

    TEST(VariantTests, ConstructEmptyArray) {
        ced_var_p arr[] = {};

        ced_var_p var = ced_var_new_array(arr, 0);

        EXPECT_EQ(var->type, ced_var_type_array);
        EXPECT_EQ(var->size, 0);

        ced_var_free(var);
    }

    TEST(VariantTests, ConstructArray) {
        ced_var_p arr[] = {
            ced_var_new_int8(10),
            ced_var_new_int16(500),
            ced_var_new_int32(100000),
            ced_var_new_int64(10000000000),
            ced_var_new_string("Howdy!")
        };

        ced_var_p var = ced_var_new_array(arr, 5);

        EXPECT_EQ(var->type, ced_var_type_array);
        EXPECT_EQ(var->size, 5);

        for (int i = 0; i < 5; ++i) {
            ced_var_free(arr[i]);
        }
        ced_var_free(var);
    }

    TEST(VariantTests, GetThirdItemFromArray) {
        ced_var_p arr[] = {
                ced_var_new_int8(10),
                ced_var_new_int16(500),
                ced_var_new_int32(100000),
                ced_var_new_int64(10000000000),
                ced_var_new_string("Howdy!")
        };

        ced_var_p var = ced_var_new_array(arr, 5);

        ced_var_p third = ced_var_array_get(var, 2);
        EXPECT_EQ(third->type, ced_var_type_int32);
        EXPECT_EQ(third->data._int32, 100000);

        for (int i = 0; i < 5; ++i) {
            ced_var_free(arr[i]);
        }
        ced_var_free(var);
    }

    TEST(VariantTests, AsType) {
        ced_var_p var = ced_var_new_int8(1);
        ced_var_p new_var = ced_var_as_type(var, ced_var_type_int16);
        EXPECT_EQ(new_var->type, ced_var_type_int16);
        EXPECT_EQ(new_var->data._int16, 1);
        ced_var_free(var);
        ced_var_free(new_var);
    }

    TEST(VariantTests, AsTypeFail) {
        ced_var_p var = ced_var_new_int64(1);
        ced_var_p new_var = ced_var_as_type(var, ced_var_type_int8);
        EXPECT_EQ(new_var == NULL, true);

        ced_var_free(var);
    }
}