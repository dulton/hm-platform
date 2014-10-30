/*
 * hm_netbuf.h
 *
 * This file describes net ring buffer.
 *
 * Copyright(c) by HiMickey, 2010~2014
 * Author:
 *
*/

#ifndef __JPF_NETBUF_H__
#define __JPF_NETBUF_H__

#define PAGE_SIZE				4096
#define MAX_IO_BUFFER_SIZE		(16*PAGE_SIZE)    //64K

typedef struct _JNetBuf JNetBuf;

typedef int (*JNetBufFlush)(
	char *buf, size_t count, void *user_data);

#ifdef __cplusplus
extern "C" {
#endif

JNetBuf *hm_net_buf_alloc(int n_blocks, JNetBufFlush flush);
void hm_net_buf_free(JNetBuf *buff);

int hm_net_buf_write(JNetBuf *buff, char *buf, size_t count,
	void *user_data, int *pending);

int hm_net_buf_flush(JNetBuf *buff, void *user_data);

#ifdef __cplusplus
}
#endif

#endif  //__JPF_NETBUF_H__
