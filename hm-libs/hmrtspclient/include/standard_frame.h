#ifndef __FRAME_DEFINITION_FOR_JXJ_PLATFORM_H__
#define __FRAME_DEFINITION_FOR_JXJ_PLATFORM_H__

#include <stdint.h>

/* ͨ������֡���� */

typedef enum                    /* ����֡���� */
{
    F_TYPE_NULL = 0,
    F_TYPE_PICTURE,
    F_TYPE_AUDIO,
    F_TYPE_VIDEO_I_FRAME,
    F_TYPE_VIDEO_P_FRAME,
    F_TYPE_VIDEO_B_FRAME
}frame_type_t;


typedef enum                    /* �豸���� */
{
    F_DEV_HIK
}frame_dev_t;


typedef struct _standard_frame_t
{
    uint32_t    magic;          /* 0x6a786a2d */	
    uint8_t     frame_type;     /* ����֡���� */
    uint8_t     frame_ext;      /* �����������ͣ�0Ϊ�޸������� */
    uint8_t     padding[2];     /* ��� */
    uint32_t    frame_dev;      /* �������ݵ��豸���� */
    uint32_t    frame_size;     /* �����ܳ��ȣ���ͷ */
    uint32_t    time_stamp;     /* ʱ��� */
    uint8_t     data[0];        /* ���ݣ��򸽼�������ʼ */
}standard_frame_t;


typedef struct _frame_ext_t frame_ext_t;
struct _frame_ext_t
{
    uint32_t        ext_size;       /* �������ݳ��� */
    uint32_t        data[0];        /* �������ݣ�4�ֽڶ��� */
};


/* RTP�������:
        (1) PT:99 Encoding-Name:jpf-generic, Clock-Rate:90000. ���磺m�Σ�a=rtpmap:99 jframe-generic/90000
        (2) ʹ��frame��װ����ʱ����ʹ��rtp��չ����track.
        (3) ��������Ҫ�������ݣ���media�����Բ���ָ��priv���ԣ�decode-header�ֶΣ�����: m�Σ�a=priv:99 decode-header=AAAAAAAAAAABAAAAQgAAAFAW/ggDAAAAAAAAAAAAAAAATv4IQgAAAA==
        (4) ��ʽ��|RTP-Header|EL|Frame-Header|Ext|Payload|

            struct EL                   //@{Encapsulation Layer for network transmission}
            {
                uint8_t magic;          //���ݼ��Ļ�����0xAA
                uint8_t frame_no;       //ͬһ֡�𿪵�Ƭ������ͬ��frame_no
                uint8_t total_frags;    //�ܹ��ֳ��˼�Ƭ
                uint8_t frag_no;        //��ǰ�ǵڼ�Ƭ,��1��ʼ
            };

*/


#endif  /* __FRAME_DEFINITION_FOR_JXJ_PLATFORM_H__ */
