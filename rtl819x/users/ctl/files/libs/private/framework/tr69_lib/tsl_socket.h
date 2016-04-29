/**************************************************************************
 *
 *	��Ȩ:	
 *              
 *
 *	�ļ���:	
 *              tsl_socket.h
 *
 *	����:	
 *              ף���� 
 *
 *	��������:	
 *		
 *            
 *	�����б�:	
 *             
 *              
 *      ��ʷ:
 *              $Id: $ 
 *		
 **************************************************************************/
#ifndef TSL_SOCKET_H
#define TSL_SOCKET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tsl_common.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>

/**************************************************************************
 *	[������]:
 *	        tsl_socket_tcp_open
 *
 *	[��������]:
 *              ����TCP/IP����
 *
 *	[��������]
 *  		IN tsl_char_t ip    �Է�IP��ַ
 *              IN tsl_int_t  port  �Է��˿ں�
 *
 *	[��������ֵ]
 *              >=1       TCP/IP���Ӿ��
 *              TSL_RV_ERR ʧ��
 *
 *************************************************************************/
tsl_int_t tsl_socket_tcp_open(IN tsl_char_t *ip,
                              IN tsl_int_t  port);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tsl_socket_local_open
 *
 *	[DESCRIPTION]:
 *              Open AF_LOCAL socket
 *
 *	[ARGUMENT]
 *  		IN tsl_int_t port 
 *            
 *	[RETURN]
 *              >=1          SUCCESS
 *              TSL_RV_ERR   ERROR
 *
**************************************************************************/
tsl_int_t tsl_socket_local_open(tsl_char_t *p_sockfile);

/**************************************************************************
 *	[������]:
 *	        tsl_socket_tcp_close
 *
 *	[��������]:
 *              �ر�TCP/IP����
 *
 *	[��������]
 *  		IN tsl_int_t  socket_id 
 *
 *	[��������ֵ]
 *              TSL_RV_SUC �ɹ�
 *              TSL_RV_ERR ʧ��
 *
 *************************************************************************/
tsl_rv tsl_socket_tcp_close(IN tsl_int_t  socket_id);


/**************************************************************************
 *	[������]:
 *	        tsl_socket_tcp_bind
 *
 *	[��������]:
 *              ����TCP/IP�˿�
 *
 *	[��������]
 *  		IN tsl_int_t port �˿ں�
 *            
 *	[��������ֵ]
 *              >=1         ����SOCKET���
 *              TSL_RV_ERR   ʧ��
 *
**************************************************************************/
tsl_int_t tsl_socket_tcp_bind(tsl_int_t port);


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tsl_socket_local_bind
 *
 *	[DESCRIPTION]:
 *              Bind AF_LOCAL socket
 *
 *	[ARGUMENT]
 *  		IN tsl_int_t port 
 *            
 *	[RETURN]
 *              >=1          SUCCESS
 *              TSL_RV_ERR   ERROR
 *
**************************************************************************/
tsl_int_t tsl_socket_local_bind(tsl_char_t *p_sockfile);

/**************************************************************************
 *	[������]:
 *	        tsl_socket_tcp_write
 *
 *	[��������]:
 *              дTCP/IP����
 *
 *	[��������]
 *  		IN tsl_int_t  socket_id   SOCKET���
 *              IN tsl_char_t *p_buf      �����ַ���
 *              IN tsl_int_t  buf_size    �ַ�������
 *              IN tsl_int_t  flag        1 ��ʾѭ����дֱ�����㳤�� 0��ʾֻ��д
 * 
 *	[��������ֵ]
 *              >= 1       д�����ݳ���
 *              TSL_RV_ERR  ʧ��
 *
**************************************************************************/
tsl_int_t tsl_socket_tcp_write(IN tsl_int_t sock_id, 
                               IN tsl_char_t *p_buf, 
                               IN tsl_int_t buf_size,
                               IN tsl_int_t flag);
        

/**************************************************************************
 *	[������]:
 *	        tsl_socket_tcp_read
 *
 *	[��������]:
 *              ��ȡTCP/IP����
 *
 *	[��������]
 *  		IN    tsl_int_t  socket_id   SOCKET���
 *              INOUT tsl_char_t *p_buf      ��ȡ�ַ���
 *              IN    tsl_int_t  buf_size    �ַ�������
 *              IN tsl_int_t  flag           1 ��ʾѭ����дֱ�����㳤�� 0��ʾֻ��д
 *            
 *	[��������ֵ]
 *              >= 1       ��ȡ���ݳ���
 *              TSL_RV_ERR  ʧ��
 *
**************************************************************************/
tsl_int_t tsl_socket_tcp_read(IN    tsl_int_t sock_id,
                              INOUT tsl_char_t *p_buf, 
                              IN    tsl_int_t buf_size,
                              IN    tsl_int_t flag);
	
	
#ifdef __cplusplus
}
#endif

#endif






