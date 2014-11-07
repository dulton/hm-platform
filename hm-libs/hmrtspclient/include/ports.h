#ifndef __JPF_PORTS_H__
#define __JPF_PORTS_H__

#include <glib.h>

//@{
#define E_NOMEM			1
#define E_OUTOFPORTS 	1
#define __export
//:}

/* ����ȱʡ�˿ڷ�Χ */
gint jpf_media_ports_set_default_range( void );

/* ���ö˿ڷ�Χ */
gint jpf_media_ports_set_range(gint low, gint hi);

/* ����Ҫ�ų��Ķ˿� */
void jpf_media_ports_set_reserved(gint port);

/* ���һ���˿� */
gint jpf_media_ports_get_one(gint *p_port);

/* �ͷ�һ���˿� */
void jpf_media_ports_put_one(gint port);

/* ���һ�Զ˿�: n(ż��), n+1 */
gint jpf_media_ports_get_pair(gint *p_low, gint *p_hi);

/* �ͷ�һ�Զ˿� */
void jpf_media_ports_put_pair(gint low, gint hi);

/* ��ö˿ڷ�Χ */
gint jpf_media_ports_get_range(gint *p_low, gint *p_hi);

#endif	//__JPF_PORTS_H__
