//

#include "stdafx.h"
#include <winsock2.h>
#include <conio.h>
#pragma   comment(lib,"wsock32.lib")
SOCKET sockClient;
DWORD WINAPI Great_Thread(PVOID pMyPara);
BOOL kh_exit=FALSE;
int main(int argc, char* argv[])
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	SOCKADDR_IN addrSrv;
	char msg[256];
	printf("�����������IP��");
	scanf("%s",msg);
	wVersionRequested = MAKEWORD( 1, 1 );
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) 
	{
		return 0;
	}
	if ( LOBYTE( wsaData.wVersion ) != 1 ||
        HIBYTE( wsaData.wVersion ) != 1 ) {
		WSACleanup( );
		return 0; 
	}
	sockClient=socket(AF_INET,SOCK_STREAM,0);
	addrSrv.sin_addr.S_un.S_addr=inet_addr(msg);//
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6143);
	if(-1==connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR)))
	{
		printf("���ӷ�����ʧ��");
		closesocket(sockClient);
		WSACleanup();
		return 0;
	}
	else 
	{
		printf("���ӷ������ɹ�����ʼ����\n");
		CreateThread(NULL, 0, Great_Thread, NULL, 0, NULL); 
		while(1)
		{
			printf("��˵��");
			scanf("%s",msg);
			if(msg[0]=='*')break;
			send(sockClient,msg,strlen(msg)+1,0);
			if(kh_exit)break;
		}
	}
	printf("\n�����ѶϿ����������\n");getch();
	return 0;
}
DWORD WINAPI Great_Thread(PVOID pMyPara)
{
	char msg[256];
	while(1)
	{
		if(-1==recv(sockClient,msg,256,0)){kh_exit=TRUE;break;}
		printf("\b\b\b\b\b\b����Ϣ��%s\n��˵��",msg);
	}
	closesocket(sockClient);//����˼��
	WSACleanup();
	return 0; 
}