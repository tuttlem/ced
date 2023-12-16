#ifndef __ced_reflect_h__
#define __ced_reflect_h__

typedef enum {
    reflect_type_none = 0,
    reflect_type_btree = 1,
    reflect_type_btree_node = 2,
    reflect_type_graph = 3,
    reflect_type_graph_node = 4,
    reflect_type_graph_edge = 5,
    reflect_type_list = 6,
    reflect_type_list_node = 7,
    reflect_type_queue = 8,
    reflect_type_stack = 10,
    reflect_type_variant = 12,
    reflect_type_htable = 13,
    reflect_type_htable_node = 14,
    reflect_type_buffer = 15,
    reflect_type_server = 16,
    reflect_type_server_client = 17,
} ced_reflect_type_t;

typedef struct {
    ced_reflect_type_t type;
} ced_reflect_info_t, *ced_reflect_info_p;

#define CED_REFLECT_INFO ced_reflect_info_t __info;
#define ced_reflect_info(obj) obj->__info
#define ced_reflect_set_info(obj, t) obj->__info.type = t

#endif /* __ced_reflect_h__ */