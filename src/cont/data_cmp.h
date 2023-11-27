#ifndef __ced_ds_types_h__
#define __ced_ds_types_h__

#include <string.h>
#include <stdint.h>

#include "../reflect.h"

/**
 * @brief Generic pointer data comparator function type.
 */
typedef int(*ced_data_cmp)(const void *, const void *);

extern ced_data_cmp ced_data_cmp_default;
extern ced_data_cmp ced_data_cmp_str;
extern ced_data_cmp ced_data_cmp_int32;

#endif /* __ced_ds_types_h__ */