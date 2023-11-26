#ifndef __ced_var_variant_h__
#define __ced_var_variant_h__

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../reflect.h"

typedef enum {
    ced_var_type_null = 0,
    ced_var_type_int8 = 1,
    ced_var_type_uint8 = 2,
    ced_var_type_int16 = 3,
    ced_var_type_uint16 = 4,
    ced_var_type_int32 = 5,
    ced_var_type_uint32 = 6,
    ced_var_type_int64 = 7,
    ced_var_type_uint64 = 8,
    ced_var_type_bool = 9,
    ced_var_type_float = 10,
    ced_var_type_double = 11,
    ced_var_type_string = 12,
    ced_var_type_pointer = 13,

    /* always an array of variants */
    ced_var_type_array = 14,

    /* keys are always strings, values are always variants */
    ced_var_type_dict = 15,
} ced_var_type_t;

static size_t ced_var_type_sizes[16];

#define ced_var_type_is_null(type)      (type == ced_var_type_null)
#define ced_var_type_is_int(type)       (type >= ced_var_type_int8 && type <= ced_var_type_bool)
#define ced_var_type_is_decimal(type)   (type >= ced_var_type_float && type <= ced_var_type_double)
#define ced_var_type_is_string(type)    (type == ced_var_type_string)
#define ced_var_type_is_pointer(type)   (type == ced_var_type_pointer || type == ced_var_type_string)

// Variant data structure
typedef struct ced_var_t {
    CED_REFLECT_INFO
    ced_var_type_t type;
    size_t size;

    union {
        int8_t _int8;
        uint8_t _uint8;
        int16_t _int16;
        uint16_t _uint16;
        int32_t _int32;
        uint32_t _uint32;
        int64_t _int64;
        uint64_t _uint64;
        int _bool;
        float _float;
        double _double;
        char* _string;
        void* _pointer;
        struct ced_var_t **_array;
    } data;
} ced_var_t, *ced_var_p;

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_int8(int8_t value);

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_int16(int16_t value);

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_int32(int32_t value);

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_int64(int64_t value);

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_uint8(uint8_t value);

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_uint16(uint16_t value);

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_uint32(uint32_t value);

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_uint64(uint64_t value);

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_bool(int value);

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_float(float value);

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_double(double value);

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_string(const char* value);

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_pointer(void* value);

/**
 * @brief Create a new variant array
 * @param values A pointer to the values for the variant to hold
 * @param length The length of the array
 * @return A new variant structure
 */
ced_var_p ced_var_new_array(ced_var_p* values, size_t length);

/**
 * @brief Retrieves an item from a variant array
 * @param var The variant array to retrieve from
 * @param index The index of the item to retrieve
 * @return The variant at the specified index
 */
ced_var_p ced_var_array_get(ced_var_p var, size_t index);

/**
 * @brief Frees a variant structure
 * @param var The variant to free
 */
void ced_var_free(ced_var_p var);

/**
 * @brief Clones a variant structure
 * @param var The variant to clone
 * @return A new variant structure
 */
ced_var_p ced_var_clone(ced_var_p var);

/**
 * @brief Converts a variant to the requested type
 * @param var The variant to convert
 * @param type The type to convert to
 * @return The converted variant
 */
ced_var_p ced_var_as_type(ced_var_p var, ced_var_type_t type);

#define ced_var_as_int8(var)   ced_var_as_type(var, ced_var_type_int8)
#define ced_var_as_int16(var)  ced_var_as_type(var, ced_var_type_int16)
#define ced_var_as_int32(var)  ced_var_as_type(var, ced_var_type_int32)
#define ced_var_as_int64(var)  ced_var_as_type(var, ced_var_type_int64)
#define ced_var_as_uint8(var)  ced_var_as_type(var, ced_var_type_uint8)
#define ced_var_as_uint16(var) ced_var_as_type(var, ced_var_type_uint16)
#define ced_var_as_uint32(var) ced_var_as_type(var, ced_var_type_uint32)
#define ced_var_as_uint64(var) ced_var_as_type(var, ced_var_type_uint64)
#define ced_var_as_bool(var)   ced_var_as_type(var, ced_var_type_bool)
#define ced_var_as_float(var)  ced_var_as_type(var, ced_var_type_float)
#define ced_var_as_double(var) ced_var_as_type(var, ced_var_type_double)
#define ced_var_as_string(var) ced_var_as_type(var, ced_var_type_string)
#define ced_var_as_ptr(var)    ced_var_as_type(var, ced_var_type_pointer)
#define ced_var_as_array(var)  ced_var_as_type(var, ced_var_type_array)
#define ced_var_as_dict(var)   ced_var_as_type(var, ced_var_type_dict)

#endif /* __ced_var_variant_h__ */