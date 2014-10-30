#ifndef __J_MEM_H__
#define __J_MEM_H__

#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif

void *hm_alloc(size_t size);
void *hm_alloc0(size_t size);
void _hm_dealloc(void *ptr, size_t size);

#define hm_dealloc(ptr, size) \
	_hm_dealloc(ptr, size)

#define hm_new(struct_type, count) \
	hm_alloc(sizeof(struct_type)*(count))

#define hm_new0(struct_type, count) \
	hm_alloc0(sizeof(struct_type)*(count))

#define hm_del(ptr, struct_type, count) \
	_hm_dealloc((ptr), sizeof(struct_type)*(count))

#ifdef __cplusplus
}
#endif

#endif	//__J_MEM_H__
