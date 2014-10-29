#ifndef __J_XML_MEMORY_H__
#define __J_XML_MEMORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define J_ASSERT(exp) 		assert(exp);


typedef void *(*alloc_t)(size_t size);
typedef void (*dealloc_t)(void *ptr, size_t size);

typedef void *(*g_alloc_t)(size_t size);
typedef void (*g_dealloc_t)(void *ptr, size_t size);

#ifdef __cplusplus
extern "C" {
#endif

	void *hm_xml_alloc(size_t size);
	void hm_xml_dealloc(void *ptr, size_t size);

#ifdef __cplusplus
}
#endif

#endif	//__J_XML_MEMORY_H__
