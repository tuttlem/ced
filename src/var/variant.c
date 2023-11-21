
#include "./variant.h"

static size_t ced_var_type_sizes[] = {
        0,
        sizeof(int8_t),
        sizeof(uint8_t),
        sizeof(int16_t),
        sizeof(uint16_t),
        sizeof(int32_t),
        sizeof(uint32_t),
        sizeof(int64_t),
        sizeof(uint64_t),
        sizeof(int),
        sizeof(float),
        sizeof(double),
        sizeof(char*),
        sizeof(void*)
};

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_int8(int8_t value) {
    ced_var_p var = malloc(sizeof(ced_var_t));
    var->type = ced_var_type_int8;
    var->data._int8 = value;

    return var;
}

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_int16(int16_t value) {
    ced_var_p var = malloc(sizeof(ced_var_t));
    var->type = ced_var_type_int16;
    var->data._int16 = value;

    return var;
}

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_int32(int32_t value) {
    ced_var_p var = malloc(sizeof(ced_var_t));
    var->type = ced_var_type_int32;
    var->data._int32 = value;

    return var;
}

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_int64(int64_t value) {
    ced_var_p var = malloc(sizeof(ced_var_t));
    var->type = ced_var_type_int64;
    var->data._int64 = value;

    return var;
}

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_uint8(uint8_t value) {
    ced_var_p var = malloc(sizeof(ced_var_t));
    var->type = ced_var_type_uint8;
    var->data._uint8 = value;

    return var;
}

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_uint16(uint16_t value) {
    ced_var_p var = malloc(sizeof(ced_var_t));
    var->type = ced_var_type_uint16;
    var->data._uint16 = value;

    return var;
}

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_uint32(uint32_t value) {
    ced_var_p var = malloc(sizeof(ced_var_t));
    var->type = ced_var_type_uint32;
    var->data._uint32 = value;

    return var;
}

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_uint64(uint64_t value) {
    ced_var_p var = malloc(sizeof(ced_var_t));
    var->type = ced_var_type_uint64;
    var->data._uint64 = value;

    return var;
}

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_bool(int value) {
    ced_var_p var = malloc(sizeof(ced_var_t));
    var->type = ced_var_type_bool;
    var->data._bool = value;

    return var;
}

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_float(float value) {
    ced_var_p var = malloc(sizeof(ced_var_t));
    var->type = ced_var_type_float;
    var->data._float = value;

    return var;
}

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_double(double value) {
    ced_var_p var = malloc(sizeof(ced_var_t));
    var->type = ced_var_type_double;
    var->data._double = value;

    return var;
}

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_string(const char* value) {
    ced_var_p var = malloc(sizeof(ced_var_t));
    var->type = ced_var_type_string;
    var->data._string = strdup(value);

    return var;
}

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_pointer(void* value) {
    ced_var_p var = malloc(sizeof(ced_var_t));
    var->type = ced_var_type_pointer;
    var->data._pointer = value;

    return var;
}

/**
 * @brief Frees a variant structure
 * @param var The variant to free
 */
void ced_var_free(ced_var_p var) {
    assert(var != NULL);

    if (var->type == ced_var_type_string && var->data._string != NULL) {
        free(var->data._string);
    } else if (var->type == ced_var_type_pointer && var->data._pointer != NULL) {
        free(var->data._pointer);
    }

    free(var);
}

/**
 * @brief Converts a variant to the requested type
 * @param var The variant to convert
 * @param type The type to convert to
 * @return The converted variant
 */
ced_var_p ced_var_as_type(ced_var_p var, ced_var_type_t type) {
    assert(var != NULL);

    if (var->type == type) {
        return var;
    }

    if (ced_var_type_sizes[var->type] > ced_var_type_sizes[type]) {
        return NULL;
    }

    ced_var_p new_var = malloc(sizeof(ced_var_t));
    new_var->type = type;

    switch (type) {
        case ced_var_type_int8:
            new_var->data._int8 = var->data._int8;
            break;
        case ced_var_type_int16:
            new_var->data._int16 = var->data._int16;
            break;
        case ced_var_type_int32:
            new_var->data._int32 = var->data._int32;
            break;
        case ced_var_type_int64:
            new_var->data._int64 = var->data._int64;
            break;
        case ced_var_type_uint8:
            new_var->data._uint8 = var->data._uint8;
            break;
        case ced_var_type_uint16:
            new_var->data._uint16 = var->data._uint16;
            break;
        case ced_var_type_uint32:
            new_var->data._uint32 = var->data._uint32;
            break;
        case ced_var_type_uint64:
            new_var->data._uint64 = var->data._uint64;
            break;
        case ced_var_type_bool:
            new_var->data._bool = var->data._bool;
            break;
        case ced_var_type_float:
            new_var->data._float = var->data._float;
            break;
        case ced_var_type_double:
            new_var->data._double = var->data._double;
            break;
        case ced_var_type_string:
            new_var->data._string = var->data._string;
            break;
        case ced_var_type_pointer:
            new_var->data._pointer = var->data._pointer;
            break;
        default:
            assert(NULL);
    }

    return new_var;
}