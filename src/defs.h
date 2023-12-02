#ifndef __ced_defs_h__
#define __ced_defs_h__

#define CED_SUCCESS     0
#define CED_FAILURE     -1

typedef enum {
    ced_encoding_none = 0,
    ced_encoding_hex = 1,
    ced_encoding_base64 = 2,
    ced_encoding_ascii = 3,
} ced_encoding_t;

#endif /* __ced_defs_h__ */