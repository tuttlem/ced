
#include "types.h"

int _ced_data_cmp_default(const void *a, const void *b) {
    return a > b ? 1 : a < b ? -1 : 0;
}

int _ced_data_cmp_str(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

ced_data_cmp ced_data_cmp_default = _ced_data_cmp_default;
ced_data_cmp ced_data_cmp_str = _ced_data_cmp_str;