// �������2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <conio.h>
#pragma   comment(lib,"wsock32.lib")
SOCKET sockConn;//���Ӿ��
BOOL kh_exit=FALSE;
DWORD WINAPI Great_Thread(PVOID pMyPara);
int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKADDR_IN addrClient;//�ͻ���IP
	SOCKADDR_IN addrSrv;//������IP
	SOCKET sockSrv;
	char msg[256];
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD( 1, 1 );
	if (WSAStartup( wVersionRequested, &wsaData )!=0)
		return 0;
	if ( LOBYTE( wsaData.wVersion ) != 1 ||HIBYTE( wsaData.wVersion ) != 1 ) 
	{
		WSACleanup();return 0; 
	}
	sockSrv=socket(AF_INET,SOCK_STREAM,0);
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6143);
	bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
	listen(sockSrv,50);//���������
	int len=sizeof(SOCKADDR);
	printf("�Ѵ�������ˣ��ȴ��û����ӣ�\n");
	sockConn=accept(sockSrv,(SOCKADDR*)&addrClient,&len);//��������
	printf("�Ѻ��û��������ӣ���ʼ����\n");
	CreateThread(NULL, 0, Great_Thread, NULL, 0, NULL); 
	while(1)
	{
		printf("��˵��");
		scanf("%s",msg);
		send(sockConn,msg,strlen(msg)+1,0);
		if(kh_exit)break;
	}
	printf("\n�����ѶϿ����������\n");getch();
	return 0;
}
DWORD WINAPI Great_Thread(PVOID pMyPara)
{
	char msg[256];
	while(1)
	{
		if(-1==recv(sockConn,msg,256,0)){kh_exit=TRUE;break;}
		printf("\b\b\b\b\b\b����Ϣ��%s\n��˵��",msg);
	}
	closesocket(sockConn);//����˼��
	WSACleanup();
	return 0; 
}