
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
        sizeof(void*),
        0,
        0,
};

ced_var_t _ced_var_null = {
        .__info.type = reflect_type_variant,
        .type = ced_var_type_null,
        .size = 0,
        .data = {._int8 = 0}
};

ced_var_t _ced_var_true = {
        .__info.type = reflect_type_variant,
        .type = ced_var_type_bool,
        .size = 1,
        .data = {._bool = 1}
};

ced_var_t _ced_var_false = {
        .__info.type = reflect_type_variant,
        .type = ced_var_type_bool,
        .size = 1,
        .data = {._bool = 0}
};

ced_var_t _ced_var_empty_string = {
        .__info.type = reflect_type_variant,
        .type = ced_var_type_string,
        .size = 0,
        .data = {._string = ""}
};

ced_var_t _ced_var_empty_pointer = {
        .__info.type = reflect_type_variant,
        .type = ced_var_type_pointer,
        .size = 0,
        .data = {._pointer = NULL}
};

/**
 * @brief Create a new variant
 * @return A new variant structure
 */
ced_var_p _ced_var_new(ced_var_type_t type) {
    ced_var_p var = malloc(sizeof(ced_var_t));
    var->__info.type = reflect_type_variant;
    var->type = type;
    var->size = ced_var_type_sizes[type];
    var->data._uint64 = 0;

    return var;
}

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_int8(int8_t value) {
    ced_var_p var = _ced_var_new(ced_var_type_int8);
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
    var->__info.type = reflect_type_variant;
    var->type = ced_var_type_int16;
    var->size = ced_var_type_sizes[var->type];

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
    var->__info.type = reflect_type_variant;
    var->type = ced_var_type_int32;
    var->size = ced_var_type_sizes[var->type];

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
    var->__info.type = reflect_type_variant;
    var->type = ced_var_type_int64;
    var->size = ced_var_type_sizes[var->type];

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
    var->__info.type = reflect_type_variant;
    var->type = ced_var_type_uint8;
    var->size = ced_var_type_sizes[var->type];

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
    var->__info.type = reflect_type_variant;
    var->type = ced_var_type_uint16;
    var->size = ced_var_type_sizes[var->type];

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
    var->__info.type = reflect_type_variant;
    var->type = ced_var_type_uint32;
    var->size = ced_var_type_sizes[var->type];

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
    var->__info.type = reflect_type_variant;
    var->type = ced_var_type_uint64;
    var->size = ced_var_type_sizes[var->type];

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
    var->__info.type = reflect_type_variant;
    var->type = ced_var_type_bool;
    var->size = ced_var_type_sizes[var->type];

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
    var->__info.type = reflect_type_variant;
    var->type = ced_var_type_float;
    var->size = ced_var_type_sizes[var->type];

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
    var->__info.type = reflect_type_variant;
    var->type = ced_var_type_double;
    var->size = ced_var_type_sizes[var->type];

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
    var->__info.type = reflect_type_variant;
    var->type = ced_var_type_string;
    var->data._string = strdup(value);
    var->size = strlen(value);

    return var;
}

/**
 * @brief Create a new variant
 * @param value The value for the variant to hold
 * @return A new variant structure
 */
ced_var_p ced_var_new_pointer(void* value) {
    ced_var_p var = malloc(sizeof(ced_var_t));
    var->__info.type = reflect_type_variant;
    var->type = ced_var_type_pointer;
    var->size = ced_var_type_sizes[var->type];
    var->data._pointer = value;

    return var;
}

/**
 * @brief Clones a variant into a new variant
 * @param var The variant to clone
 * @return A new variant structure
 */
ced_var_p ced_var_clone(ced_var_p var) {
    assert(var != NULL);

    ced_var_p new_var = malloc(sizeof(ced_var_t));
    ced_reflect_set_info(new_var, reflect_type_variant);

    new_var->type = var->type;
    new_var->size = var->size;

    memcpy(new_var, var, sizeof(ced_var_t));

    switch (var->type) {
        case ced_var_type_string:
            new_var->data._string = strdup(var->data._string);
            break;

        case ced_var_type_pointer:
            new_var->data._pointer = var->data._pointer;
            break;

        case ced_var_type_array:
            new_var->data._array = malloc(sizeof(ced_var_p) * var->size);

            ced_var_p *item = new_var->data._array;
            for (size_t i = 0; i < var->size; ++i) {
                item[i] = ced_var_clone(var->data._array[i]);
            }

            break;
    }

    return new_var;

}

/**
 * @brief Create a new variant array
 * @param values A pointer to the values for the variant to hold
 * @param length The length of the array
 * @return A new variant structure
 */
ced_var_p ced_var_new_array(ced_var_p* values, size_t length) {
    ced_var_p var = _ced_var_new(ced_var_type_array);

    /* when we're talking an array, the size is the length */
    var->size = length;

    /* duplicate the array of variants pointed to by values, into our new variant */
    var->data._array = malloc(sizeof(ced_var_p) * var->size);

    /* copy each variant into the new array */
    for (size_t i = 0; i < var->size; ++i) {
        var->data._array[i] = ced_var_clone(values[i]);
    }

    return var;
}

/**
 * @brief Retrieves an item from a variant array
 * @param var The variant array to retrieve from
 * @param index The index of the item to retrieve
 * @return The variant at the specified index
 */
ced_var_p ced_var_array_get(ced_var_p var, size_t index) {
    assert(var != NULL);
    assert(var->type == ced_var_type_array);
    assert(index < var->size);

    return var->data._array[index];
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
    } else if (var->type == ced_var_type_array && var->data._array != NULL) {
        // free each of the variants in the array
        for (size_t i = 0; i < var->size; ++i) {
            ced_var_free(var->data._array[i]);
        }

        // free the array itself
        free(var->data._array);
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
    ced_reflect_set_info(new_var, reflect_type_variant);

    new_var->type = type;
    new_var->size = ced_var_type_sizes[type];

    switch (type) {
        case ced_var_type_int8:
        case ced_var_type_int16:
        case ced_var_type_int32:
        case ced_var_type_int64:
        case ced_var_type_uint8:
        case ced_var_type_uint16:
        case ced_var_type_uint32:
        case ced_var_type_uint64:
        case ced_var_type_bool:
        case ced_var_type_float:
        case ced_var_type_double:
            memcpy(&new_var->data, &var->data, new_var->size);
            break;

        case ced_var_type_string:
            memcpy(&new_var->data._string, &var->data, new_var->size);
            break;
        case ced_var_type_pointer:
            memcpy(&new_var->data._pointer, &var->data, new_var->size);
            break;

        case ced_var_type_array:
        default:
            memcpy(new_var, &_ced_var_null, sizeof(ced_var_t));
            break;
    }

    return new_var;
}