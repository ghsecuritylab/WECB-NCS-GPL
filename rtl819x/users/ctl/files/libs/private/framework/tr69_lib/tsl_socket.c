/**************************************************************************
 *
 *	��Ȩ:	
 *              
 *
 *	�ļ���:	
 *              tsl_socket.c
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
 *              
 *		
 **************************************************************************/
#include "tsl_common.h"
#include "tsl_socket.h"

/**************************************************************************
 *
 *              TCP/IP���ܺ���ʵ��
 *
 *************************************************************************/

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
                              IN tsl_int_t  port)
{
	struct sockaddr_in 	address;
	tsl_int_t 		handle = -1;
//Coverity comment 17837
	memset(&address,0,sizeof(struct sockaddr_in));

#ifdef _WIN32
	WORD    dVer;
	WSADATA dData;
	dVer = MAKEWORD(2, 2);
	WSAStartup(dVer, &dData);
#endif 
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ip);
	address.sin_port = htons((unsigned short)port);

	handle = socket(AF_INET, SOCK_STREAM, 0);

	//Coverity CID 16835: Argument cannot be negative 
	if(handle == -1){
		return TSL_RV_ERR;
	}
    
	if( connect(handle, (struct sockaddr *)&address, sizeof(address)) == -1) {
		//Coverity ID: 17280,Resource leak, need close socket here
		close(handle);
		return TSL_RV_ERR;
	}else {
		return handle;
	}
}

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
tsl_int_t tsl_socket_local_open(tsl_char_t *p_sockfile)
{
  	static struct sockaddr_un s_un;
	tsl_int_t                 sock_id;

	memset(&s_un, 0, sizeof(s_un));
	s_un.sun_family = AF_LOCAL;
        sprintf(s_un.sun_path, p_sockfile);
	//Coverity CID 16115: Side effect in assertion (ASSERT_SIDE_EFFECT)	
	sock_id = socket(AF_LOCAL, SOCK_STREAM, 0);
       TSL_FVASSERT(sock_id != -1);
	//Coverity ID:17278, Resource leak
	TSL_FVASSERT_ACT((connect(sock_id, (struct sockaddr *)&s_un, sizeof(s_un)) >= 0), close(sock_id));
	
	return sock_id;
}


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
tsl_rv tsl_socket_tcp_close(IN tsl_int_t  socket_id)
{
	return close(socket_id);
}

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
tsl_int_t tsl_socket_tcp_bind(tsl_int_t port)
{
	static struct sockaddr_in s_in;
	tsl_int_t sock_id;
	tsl_int_t opt_val   = 1;

	memset(&s_in, 0, sizeof(s_in));
	s_in.sin_family = AF_INET;

	s_in.sin_addr.s_addr = INADDR_ANY;
	s_in.sin_port = htons(port);

	//Coverity CID 16116: Side effect in assertion (ASSERT_SIDE_EFFECT) 
	sock_id = socket(AF_INET, SOCK_STREAM, 0);
       TSL_FVASSERT(sock_id != -1);

	//Coverity ID: 17279,  Resource leak 
	TSL_FVASSERT_ACT((setsockopt(sock_id, SOL_SOCKET, SO_REUSEADDR,  (char *)&opt_val, sizeof(int)) >= 0), close(sock_id));
	TSL_FVASSERT_ACT((bind(sock_id, (struct sockaddr *)&s_in, sizeof(s_in)) >= 0), close(sock_id));
	TSL_FVASSERT_ACT((listen(sock_id, 64 ) >= 0), close(sock_id));

	return sock_id;
}

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
tsl_int_t tsl_socket_local_bind(tsl_char_t *p_sockfile)
{
  	static struct sockaddr_un s_un;
	tsl_int_t                 sock_id;
	tsl_int_t                 opt_val   = 1;

	memset(&s_un, 0, sizeof(s_un));
	s_un.sun_family = AF_LOCAL;
        sprintf(s_un.sun_path, p_sockfile);
        
        unlink(p_sockfile);

	//Coverity CID 16114: Side effect in assertion (ASSERT_SIDE_EFFECT)
	sock_id = socket(AF_LOCAL, SOCK_STREAM, 0);
	TSL_FVASSERT(sock_id != -1);

	//Coverity CID 17277: Resource leak (RESOURCE_LEAK)
	TSL_FVASSERT_ACT((setsockopt(sock_id, SOL_SOCKET, SO_REUSEADDR,  (char *)&opt_val, sizeof(int)) >= 0), close(sock_id));
	TSL_FVASSERT_ACT((bind(sock_id, (struct sockaddr *)&s_un, sizeof(s_un)) >= 0), close(sock_id));
	TSL_FVASSERT_ACT((listen(sock_id, 64 ) >= 0), close(sock_id));
	return sock_id;
}


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
 *                        �ɹ�
 *              TSL_RV_ERR ʧ��
 *
**************************************************************************/
tsl_int_t tsl_socket_tcp_write(tsl_int_t sock_id, 
                               tsl_char_t *buf, 
                               tsl_int_t buf_size,
                               tsl_int_t flag)
{
        tsl_int_t       size = 0;
        tsl_int_t 	res  = 0;

        TSL_VASSERT(sock_id > 0);
	TSL_VASSERT(buf != NULL);
	TSL_VASSERT(buf_size > 0);
	
	while(size < buf_size){
        	res = send(sock_id, (char *)buf + size, buf_size - size, 0);
   		if (res <= 0){
			return -1;
		}
        	size += res;
		if (!flag){
			return size;
		}
        }
	
	return size;
	
}


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
                              INOUT tsl_char_t *buf, 
                              IN    tsl_int_t buf_size,
                              IN    tsl_int_t flag)
{
	tsl_int_t 	size = 0;
	tsl_int_t 	res  = 0;

        TSL_VASSERT(sock_id > 0);
	TSL_VASSERT(buf != NULL);
	TSL_VASSERT(buf_size > 0);
	
	while(size < buf_size){
		res = recv(sock_id, (char *)buf + size, buf_size - size, 0); 
        	if(res <= 0 ){
			return -1;
		}
                
		size += res;
		if (!flag){
			return size;
		}
	}
	
        return size;
}
