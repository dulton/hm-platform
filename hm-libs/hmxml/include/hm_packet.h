
#ifndef __J_XML_PACKET_H__
#define __J_XML_PACKET_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hm_sdk.h"


typedef struct __Request
{
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_or_gu_id[J_SDK_MAX_ID_LEN];

	int reserve;		//1. ��ȡ������Ϣ: ���ں�
						//2. ��������: ��������
}Request;

typedef struct __Result
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_or_gu_id[J_SDK_MAX_ID_LEN];
	
	int reserve;		//1. ���Ѳ��·��: Ѳ��·����
}Result;


//==================================================

typedef struct __PuGetCss
{
	JResultCode result;
	char css_ip[J_SDK_MAX_IP_LEN];
    int  css_port;
    char dev_code[J_SDK_MAX_ID_LEN];            //�豸�������
    char software_ver[J_SDK_MAX_VERSION_LEN];   //�豸����汾
}PuGetCssPacket;

typedef struct __PuRegisterCss
{
    char dev_code[J_SDK_MAX_ID_LEN];            //�豸�������
	char dev_ip[J_SDK_MAX_IP_LEN];
	char css_ip[J_SDK_MAX_IP_LEN];
    char software_ver[J_SDK_MAX_VERSION_LEN];   //�豸����汾
}PuRegisterCssPacket;

typedef struct __RegisterRequestPacket
{
	char pu_id[J_SDK_MAX_ID_LEN];				//�����豸��PUID��
	char dev_ip[J_SDK_MAX_IP_LEN];
	char cms_ip[J_SDK_MAX_IP_LEN];
	JPuType pu_type;
}RegisterRequestPacket;

typedef struct __RegisterResponsePacket
{
	JResultCode result;
	char pu_id[J_SDK_MAX_ID_LEN];
	char mds_ip[J_SDK_MAX_IP_LEN];
	int mds_port;
	int keep_alive;
}RegisterResponsePacket;

typedef struct __HeartBeatRequestPacket
{
	char pu_id[J_SDK_MAX_ID_LEN];
	char dev_ip[J_SDK_MAX_IP_LEN];
}HeartBeatRequestPacket;

typedef struct __HeartBeatResponsePacket
{
	JResultCode result;
	JTime server_time;
	int plt_type;	//1:��ƽ̨
}HeartBeatResponsePacket;


//##########################################################

typedef struct __MdsInfoPacket
{
	JResultCode result;
	char pu_id[J_SDK_MAX_ID_LEN];
	char cms_ip[J_SDK_MAX_IP_LEN];
	char mds_ip[J_SDK_MAX_IP_LEN];
	int mds_port;
}MdsInfoPacket;


typedef struct __ChangeDispatchPacket
{
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	char mds_ip[J_SDK_MAX_IP_LEN];
	int mds_port;
}ChangeDispatchPacket;

typedef struct __DeviceInfoPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	char manu_info[J_SDK_MAX_MANU_INFO_LEN];	//������Ϣ
	char release_date[J_SDK_MAX_DATA_LEN];		//��������
	char dev_version[J_SDK_MAX_VERSION_LEN];	//�豸�汾
	char hw_version[J_SDK_MAX_VERSION_LEN];		//Ӳ���汾
	int pu_type;								//�豸���ͣ������JPuType
	int sub_type;								//�豸�Ļ������ͣ�ָ�豸��С�࣬�����JPuSubType
	int di_num;									//�豸����ӿ���Ŀ
	int do_num;									//�豸����ӿ���Ŀ
	int channel_num;							//ͨ����Ŀ
	int rs485_num;								//485�ӿ���Ŀ����0������
	int rs232_num;								// RS22 �ӿ���Ŀ����0������
}DeviceInfoPacket;

typedef struct __DeviceNTPInfoPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	char ntp_server_ip[J_SDK_MAX_IP_LEN];		//NTP������
	int time_zone;								//ʱ��
	int time_interval;							//��ʱ���
	int ntp_enable;								//ntp���أ�1��������0��������
	int dst_enable;								//����ʱ��1��������0��������
	int reserve;								//�����ֽ�
}DeviceNTPInfoPacket;

typedef struct __DeviceTimePacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	JTime time;									//ʱ��
	int zone;									//ʱ��
	int sync_enable;							//��ƽ̨������ʱ��ͬ���Ƿ���Ч
	int set_flag;								//0: ����Ч��1: ��ʱ����Ч��2: ��ͬ����Ч
}DeviceTimePacket;

typedef struct __PlatformInfoPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	char cms_ip[J_SDK_MAX_IP_LEN];				//ƽ̨cms ip
	char mds_ip[J_SDK_MAX_IP_LEN];				//ƽ̨mds ip
	int cms_port;								//ƽ̨cms�˿ں�
	int mds_port;								//ƽ̨mds�˿ں�
	int protocol;								//�������Ĵ���Э�飬�����JProtocolType 
	int is_con_cms;								//�Ƿ�����ƽ̨��0: ����ƽ̨
}PlatformInfoPacket;

typedef struct __NetworkInfoPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	JNetwork network[J_SDK_MAX_NETWORK_TYPE];	//����ӿ���Ϣ
	char main_dns[J_SDK_MAX_DNS_LEN];			//��DNS��������ַ
	char backup_dns[J_SDK_MAX_DNS_LEN];			//����DNS��������ַ
	int auto_dns_enable;						//�Ƿ������Զ���ȡdns
	int cur_network;							//eth0/wifi/3G
	int cmd_port;								//�豸����˿�
	int data_port;								//�豸���ݶ˿�
	int web_port;								//�豸web�˿�
	int talk_port;                              //�豸�Խ��˿�
}NetworkInfoPacket;

typedef struct __PPPOEInfoPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	int type;									//PPPOE���ŵ�����ӿڣ������JNetworkType
	int enable;									//
	char ip[J_SDK_MAX_IP_LEN];					//
	char account[J_SDK_MAX_ACCOUNT_LEN];		//PPPOE�����˺�
	char passwd[J_SDK_MAX_PASSWD_LEN];			//PPPOE��������
}PPPOEInfoPacket;

typedef struct __EncodeParameterPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	int level;					//�������ͣ���(0)����(1)����(2)
	int frame_rate;				//֡��
	int i_frame_interval;		//I֡���
	int video_type;				//��Ƶ�������ͣ������JAVCodeType
	int audio_type; 			//��Ƶ�������ͣ������JAVCodeType
	int au_in_mode;				//��Ƶ�������ͣ������JAudioInputType
	int audio_enble;			//��Ƶ�Ƿ��
	int resolution;				//�ֱ��ʣ������JResolution
	int qp_value;				//����
	int code_rate;				//����
	int frame_priority;			//�Ƿ�֡������
	int format;					//��ʽ�������JVideoFormat 
	int bit_rate;				//λ�����ͣ������JBitRate
	int encode_level;			//�������ͣ������JEncodeLevel
}EncodeParameterPacket;

typedef struct __DisplayParameterPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	int contrast;				//�Աȶ�
	int bright;					//����
	int hue;					//�Ҷ�
	int saturation;				//���Ͷ�
	int sharpness;				//���
}DisplayParameterPacket;

typedef struct __RecordParameterPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	int level;					//�������ͣ���(0)����(1)����(2)
	int pre_record;				//ͨ��Ԥ¼ʱ������λ����
	int auto_cover;				//ͨ��¼���Ƿ��Զ�����

	JWeek week;
}RecordParameterPacket;

typedef struct __HideParameterPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	int hide_enable;			//�Ƿ������ڵ�
	int hide_color;				//�ڵ�ʱʹ�õ���ɫ
	JArea hide_area;			//�ڵ�����,��ĿΪ0���ڵ���Ч
	int max_width;				//�����
	int max_height;				//���߶�
}HideParameterPacket;

typedef struct __SerialParameterPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	int serial_no;				//���ں�
	int baud_rate;				//������
	int data_bit;				//����λ 
	int stop_bit;				//ֹͣλ
	int verify;					//У��
}SerialParameterPacket;

typedef struct __OSDParameterPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	int time_enable;					//�Ƿ���ʾʱ�䣻1����ʾ��0������
	int time_display_x;					//ʱ������X
	int time_display_y;					//ʱ������Y
	int time_display_color;				//ʱ����ʾ��ɫ
	int text_enable;					//�Ƿ��ı���ʾ��1����ʾ��0������
	int text_display_x;					//�ı�����X
	int text_display_y;					//�ı�����Y
	int text_display_color;				//�ı���ʾ��ɫ
	int max_width;						//�����
	int max_height;						//���߶�
	char text_data[J_SDK_MAX_TEXT_DATA_LEN];
	int stream_enable;					//�Ƿ���ʾ������Ϣ��1����ʾ��0������
	
	int time_display_w;					//ʱ��OSD ��ʾ���
	int time_display_h;					//ʱ��OSD ��ʾ�߶�
	int text_display_w;					//�ı�OSD ��ʾ���
	int text_display_h;					//�ı�OSD ��ʾ�߶�

	uint32_t osd_invert_color;				//osd ��ɫ��1��������0���ر�

	JOSDExtend ext_osd;
}OSDParameterPacket;

typedef struct __PTZParameterPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	int serial_no;						//���ں�
	int ptz_addr;						//��̨��ַ
	int protocol;						//
	int baud_rate;						//������
	int data_bit;						//����λ 
	int stop_bit;						//ֹͣλ
	int verify;							//У��
}PTZParameterPacket;

typedef struct __PTZControlPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	int action;							//��̨�����������JPTZDirection
	int param;							//���ֲ�������ֵ
}PTZControlPacket;

typedef struct __FTPParameterPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	char ftp_ip[J_SDK_MAX_IP_LEN];			//ftp������ip
	char ftp_usr[J_SDK_MAX_ACCOUNT_LEN];	//ftp������port
	char ftp_pwd[J_SDK_MAX_PASSWD_LEN];		//��½�û���
	char ftp_path[J_SDK_MAX_PATH_LEN];		//��½����
	int ftp_port;							//Ftp�ϴ�·��
}FTPParameterPacket;

typedef struct __SMTPParameterPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	char mail_ip[J_SDK_MAX_IP_LEN];			//smtp ��������ַ
	char mail_addr[J_SDK_MAX_ADDR_LEN];		//�����ʼ���ַ
	char mail_usr[J_SDK_MAX_ACCOUNT_LEN];	//�����ʼ��˺�
	char mail_pwd[J_SDK_MAX_PASSWD_LEN];	//�����ʼ�����
	char mail_rctp1[J_SDK_MAX_ADDR_LEN];	//�����ʼ���ַ1
	char mail_rctp2[J_SDK_MAX_ADDR_LEN];	//�����ʼ���ַ2
	char mail_rctp3[J_SDK_MAX_ADDR_LEN];	//�����ʼ���ַ3
	int mail_port;							//smtp �������˿�
	int ssl_enable;							//�Ƿ�����SSL
}SMTPParameterPacket;

typedef struct __UPNPParameterPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	char upnp_ip[J_SDK_MAX_IP_LEN];			//upnp ������IP
	int upnp_enable;						//upnp ����
	int upnp_eth_no;						//0ʹ�ñ�������ӳ�� 1 ʹ����������ӳ��
	int upnp_model;							//0�̶�ӳ�� 1�Զ�ӳ��
	int upnp_refresh_time;					//upnp ˢ��ʱ��(��λСʱ)
	int upnp_data_port;						//�̶�ӳ��ģʽ��, ���ݶ˿ڵ������˿�
	int upnp_web_port;						//�̶�ӳ��ģʽ��, Web�˿ڵ������˿�
	int upnp_data_port_result;				//���ݶ˿ڵ������˿� 0����û��ӳ��򲻳ɹ�
	int upnp_web_port_result;				//Web�˿ڵ������˿� 0����û��ӳ��򲻳ɹ�
	int upnp_cmd_port;                      //����˿ڵ������˿� 
    int upnp_talk_port;                     //�Խ��˿ڵ������˿� 
    int upnp_cmd_port_result;               //����˿ڵ������˿�ӳ��״̬ 0����û��ӳ��򲻳ɹ�
    int upnp_talk_port_result;              //�Խ��˿ڵ������˿�ӳ��״̬ 0����û��ӳ��򲻳ɹ�
}UPNPParameterPacket;

typedef struct __DeviceDiskInfoPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	int disk_num;
	JDiskInfo disk[J_SDK_MAX_DISK_NUMBER];
}DeviceDiskInfoPacket;	

typedef struct __FormatDiskPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	int disk_no;							//���̺�
	int progress;							//��ʽ������(0 - 100)
}FormatDiskPacket;

typedef struct __FormatProgressPacket
{
	char pu_id[J_SDK_MAX_ID_LEN];
	
	int disk_no;							//���̺�
	int progress;							//��ʽ������(0 - 100)
}FormatProgressPacket;

typedef struct __MoveAlarmPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	int move_enable;
	int sensitive_level;
	int detect_interval;
	int max_width;
	int max_height;
	JArea detect_area;
	JWeek week;
}MoveAlarmPacket;

typedef struct __LostAlarmPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	int lost_enable;
	int detect_interval;
	JWeek week;
}LostAlarmPacket;

typedef struct __HideAlarmPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	int hide_enable;
	int detect_interval;
	int sensitive_level;					//�������ֶΣ���Χ 0-4��ֵԽ�ͣ�Խ����
	int max_width;
	int max_height;
	JArea detect_area;
	JWeek week;
}HideAlarmPacket;

typedef struct __IoAlarmPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	int io_type;					//�����JIOType
	int alarm_enable;				//
	int detect_interval;			//
	JWeek week;						//
}IoAlarmPacket;

typedef struct __JointActionPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	int alarm_type;					//�����JAlarmType
	JJoint joint;					//
}JointActionPacket;

typedef struct __SubmitAlarmPacket
{
	char pu_id[J_SDK_MAX_ID_LEN];
	
	char data[J_SDK_MAX_ALARM_DATA_LEN];
	int channel;
	int alarm_type;					//��� JAlarmType
	int action_type;				//0����ʼ�澯��1�������澯
	JTime alarm_time;
}SubmitAlarmPacket;

typedef struct __MediaUrlPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	int level;						//��������
	int media_type;					//��� JMediaType
	char ip[J_SDK_MAX_IP_LEN];		//
	char url[J_SDK_MAX_URL_LEN];	//
	char cu_ip[J_SDK_MAX_IP_LEN];	//�ͻ���IP
}MediaUrlPacket;

typedef struct __StoreLogPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];

	int rec_type;
	int beg_node;
	int end_node;
	JTime beg_time;
	JTime end_time;
	
	int node_count;
	int total_count;
	int sess_id;
	Store store[J_SDK_MAX_STORE_LOG_SIZE];
}StoreLogPacket;

typedef struct __FirmwareUpgradePacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];

	int percent;
	int data_len;
	int file_len;
	int sess_id;
	char addr[J_SDK_MAX_IP_LEN];
	char data[J_SDK_MAX_UPGRADE_DATA_LEN];
}FirmwareUpgradePacket;

typedef struct __UpgradeProgressPacket
{
	char pu_id[J_SDK_MAX_ID_LEN];
	
	int percent;
}UpgradeProgressPacket;

typedef struct __ClientSimulatorConfigPacket
{
    int count;
    Channel channel[J_MAX_CHANNEL_INFO_SIZE];
}ClientSimulatorConfigPacket;

typedef struct __ChannelInfoPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	int ch_no;							//ͨ���ţ�0-255��
	int ch_type;						//ͨ������(���ء�����)
	int ch_status;						//ͨ��״̬����ֹ���������������ӣ�
	char ch_name[J_SDK_MAX_NAME_LEN];	//ͨ������
	JRemoteChannelInfo rmt_ch_info;		//Զ���豸ͨ����Ϣ
	JRemoteDeviceInfo rmt_dev_info;		//Զ���豸��Ϣ
}ChannelInfoPacket;

typedef struct __PictureInfoPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	int mirror;					//����(ͼ�����ҵ���) 1 ���� 0 ������
	int flip;					//��ת(ͼ�����µ���) 1 ��ת 0 ����ת
	int hz;						//��ԴƵ�� 0 50Hz 1 60 Hz
	int awb_mode;				//��ƽ��ģʽ 0 �Զ���ƽ�� 1�ֶ���ƽ��
	int awb_red;				//��ƽ���ɫǿ�� 0-255
	int awb_blue;				//��ƽ����ɫǿ�� 0-255
	int wdr;					//��̬0 �ر� 1-255Ϊ��̬ǿ��
	int iris_type;				//��Ȧ���� 0 �ֶ���Ȧ 1 �Զ���Ȧ
	int exp_compensation;		//�عⲹ�� 0-255
	int ae_mode;		 		//�Զ��ع�ģʽ��0-2����0 ��������	  1 ֡������	2 ��������
}PictureInfoPacket;

typedef struct __WifiConfigPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	char essid[J_SDK_MAX_ID_LEN];	//���������
	char pwd[J_SDK_MAX_PWD_LEN];	//����
	int wifi_enable;				//0���Ͽ���1������
	int encrypt_type;				//��������0:NONE  1:WPA  2:WPA2 3:WEP
	int auth_mode;					//��֤��ʽ0:NONE  1:EAP 2:PSK 3:OPEN 4:SHARED 
	int secret_key_type;			//��Կ����ʽ 0:NONE  1:AES 2:TKIP ֻ��Ӧ�ڼ�������ΪWPA/WPA2�����
	int wifi_st;					//������������״̬ 0 ������ 1 ��������2 �ɹ�
}WifiConfigPacket;

typedef struct __WifiSearchResPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	int count;				//��������wifi ����
	JWifiApInfo wifi_ap[J_SDK_MAX_WIFI_AP_SIZE];	//
}WifiSearchResPacket;

typedef struct __NetworkStatusPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	int eth_st;				//������������״̬ 0 ������ 1 ��������2 �ɹ�
	int wifi_st;			//������������״̬0 ������ 1 ��������2 �ɹ�
	int pppoe_st;			//pppoe����״̬0 ������ 1 ��������2 �ɹ�
}NetworkStatusPacket;

typedef struct __ControlDevicePacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	int command;			//������������
}ControlDevicePacket;

typedef struct __DdnsConfigPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	char ddns_account[J_SDK_MAX_NAME_LEN];		//DDNS ע����
	char ddns_usr[J_SDK_MAX_NAME_LEN];			//�û�����
	char ddns_pwd[J_SDK_MAX_PWD_LEN];			//�û�����
	int ddns_open;								//DDNS����
	int ddns_type;								//DDNS���ͣ�0-dyndns 1-3322��
	int ddns_port;								//DDNS�������˿�
	int ddns_times;								//����ʱ��
}DdnsConfigPacket;

typedef struct __AvdConfigPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
    int 		enable;                			//avd ʹ��
    JSegment	sched_time[J_SDK_MAX_SEG_SZIE]; //ʱ���
    JAvdRule	avd_rule[MAX_IVS_AVD_RULES];  	//��Ƶ��Ϲ���index �±�ȡֵ�� JAvdType
}AvdConfigPacket;


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
typedef struct __TransparentPacket
{
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char pu_id[J_SDK_MAX_ID_LEN];
	
	int type;
	int channel;
	int length;
	void *data;
}TransparentPacket;
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#ifdef _USE_DECODER_PROTO_

typedef struct __DivisionModePacket
{
	JResultCode result;
	char pu_id[J_SDK_MAX_ID_LEN];
	JDivisionMode div_mode;
}DivisionModePacket;

typedef struct __ScreenStatePacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	int dis_channel;
	JScreenState scr_state;
}ScreenStatePacket;

typedef struct __ChangeDModePacket
{
	JResultCode result;
	JChangeDMode cd_mode;
}ChangeDModePacket;

typedef struct __FullScreenPacket
{
	JResultCode result;
	JScreen screen;
}FullScreenPacket;

typedef struct __TVWallPlayPacket
{
	JResultCode result;
	JTVWallPlay tv_play;
}TVWallPlayPacket;

typedef struct __ClearDivisionPacket
{
	JResultCode result;
	JScreen screen;
}ClearDivisionPacket;

# endif //_USE_DECODER_PROTO_

typedef struct __OperationLogPacket
{
	JResultCode result;
	JOperationLog opt_log;
}OperationLogPacket;

/*typedef struct __AlarmUploadCfgPacket
{
	JResultCode result;
	JAlarmUploadCfg au_cfg;
}AlarmUploadCfgPacket;*/

typedef struct __PPConfigPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	JPPConfig pp_cfg;
}PPConfigPacket;

typedef struct __PPSetPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	JPPSet pp_set;
}PPSetPacket;

typedef struct __CruiseConfigPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	JCruiseConfig crz_cfg;
}CruiseConfigPacket;

typedef struct __CruiseWayPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	JCruiseWay crz_way;
}CruiseWayPacket;

typedef struct __CruiseWaySetPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	JCruiseWaySet crz_set;
}CruiseWaySetPacket;

typedef struct __3DControlPacket
{
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	J3DControl _3d_ctr;
}_3DControlPacket;

typedef struct __IrcutCtrlPacket
{
    JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	JIrcutCtrl ir_ctrl;
}IrcutCtrlPacket;

typedef struct __LinkIOPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	JLinkIO link_io;
}LinkIOPacket;

typedef struct __LinkPresetPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
	
	JLinkPreset link_preset;
}LinkPresetPacket;

typedef struct __ResolutionInfoPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];
    
    JResolutionInfo rsl_info;
}ResolutionInfoPacket;

typedef struct __IrcutControlPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];

    JIrcutControl ircut_ctrl;
}IrcutControlPacket;


typedef struct __ExtranetPortPacket
{
	JResultCode result;
	char session_id[J_SDK_MAX_ID_LEN];
	char domain_id[J_SDK_MAX_ID_LEN];
	char gu_id[J_SDK_MAX_ID_LEN];

    JExtranetPort extranet;
}ExtranetPortPacket;

typedef struct __HerdAnalysePacket
{
    JResultCode result;
    char session_id[J_SDK_MAX_ID_LEN];
    char domain_id[J_SDK_MAX_ID_LEN];
    char gu_id[J_SDK_MAX_ID_LEN];

    JHerdAnalyse herd_analyse;
}HerdAnalysePacket;

typedef struct __GrassPercentPacket
{
    JResultCode result;
    char session_id[J_SDK_MAX_ID_LEN];
    char domain_id[J_SDK_MAX_ID_LEN];
    char gu_id[J_SDK_MAX_ID_LEN];

    JGrassPercent grass;
}GrassPercentPacket;

typedef struct __P2PIdPacket
{
    JResultCode result;
    JP2PId p2p;
}P2PIdPacket;

typedef struct __P2PIdPacketReq
{
    JResultCode result;
    JP2PId p2p;
	int channel_count;
}P2PIdPacketReq;

#endif	//__J_XML_PACKET_H__

