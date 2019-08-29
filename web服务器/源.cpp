#pragma comment(lib, "WS2_32")
#include <cstdio>
#include <string>
#include <fstream>
#include<iostream>
#include <WinSock2.h>
#include <Windows.h>
#include<sys\stat.h>
using namespace std;
#define BUFFER_SIZE 1024
#define BUF_SIZE 50
#define HOST "127.0.0.1"
#define PORT 83
#define HEADER "\
HTTP/1.1 200 OK\r\n\
Content-Type: text/html; charset=UTF-8\r\n\
Server: DengDengServer\r\n\
Content-Length: %ld\r\n\r\n\
"
#define HEADER1 "\
HTTP/1.1 200 OK\r\n\
Content-Type: image/jpeg; charset=UTF-8\r\n\
Server: DengDengServer\r\n\
Content-Length: %ld\r\n\r\n\
"
#define HEADER2 "\
HTTP/1.1 404 Not Found\r\n\
Server: DengDengServer\r\n\r\n\
<html>\
	<head>\
        	<h1>404 Not Found</h1>\
   	</head>\
	<body>\
		<p>404 Not Found: The requested resource could not be found!</p>\
	</body>\
</html>\
"

DWORD WINAPI AcceptThread(LPVOID lpParam);


void main()
{
	WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
    {
        printf("Init socket dll error!");
        exit(1);
    }
	 //初始化本服务器的地址
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.S_un.S_addr = INADDR_ANY;
	addrServer.sin_port = htons(PORT);
	// create socket
    SOCKET socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (SOCKET_ERROR == socketServer)
    {
        printf("Create socket error!");
        exit(1);
    }
    // bind server socket host
    if (SOCKET_ERROR == bind(socketServer, (LPSOCKADDR)&addrServer, sizeof(addrServer)))
    {
        printf("Bind server host failed!");
        exit(1);
    }
    // listen
    if (SOCKET_ERROR == listen(socketServer, 100))
    {
        printf("Listen failed!");
        exit(1);
    }	
	while(true)
	{    	 
		printf("Listening ... \n");
		//启动一个接收线程
		sockaddr_in addrClient;
		int nClientAddrLen = sizeof(addrClient);
		SOCKET socketClient = accept(socketServer, (sockaddr*)&addrClient, &nClientAddrLen);      
		if (SOCKET_ERROR == socketClient)      
		{      
			printf("Accept failed!");    
			break;      
		}
		HANDLE hThread1 = CreateThread(NULL,0,AcceptThread,(LPVOID)socketClient,0,NULL);
		CloseHandle(hThread1);	
    }
    closesocket(socketServer);
    WSACleanup();
}
DWORD WINAPI AcceptThread(LPVOID lpParam)   //接收线程
{
	SOCKET socketClient=(SOCKET)lpParam;
	
	//recv
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    if (recv(socketClient, buffer, BUFFER_SIZE, 0) < 0)
    {
		printf("Recvive data failed!");
        return 0;
    }
    printf("Recv data : \n%s", buffer);

	//得到文件路径	
	int i;
	for(i=0;buffer[i]!=' ';i++)
		;
	i=i+2;
	string strPath;
	string temp;
	int j=0;
	int flag=0;
	for(;buffer[i]!=' ';i++)
	{
		strPath+=buffer[i];
		if(buffer[i-1]=='.')
			if(buffer[i]=='p'&&buffer[i+1]=='n'||buffer[i]=='j'&&buffer[i+1]=='p'||buffer[i]=='g'&&buffer[i+1]=='i') flag=1;
	}
	//send
	memset(buffer, 0, BUFFER_SIZE);

	FILE *fp = NULL;
	if ((fp = fopen(strPath.c_str(), "rb")) == NULL)
	{
		//找不到文件，返回HTTP/1.1 404
		sprintf_s(buffer, HEADER2);
		if (send(socketClient, buffer, strlen(buffer), 0) < 0)
		{
			printf("Send data failed!");
			closesocket(socketClient);
			return 0;
		}
		closesocket(socketClient);
		return 0;
	}
    //获取文件长度
	struct stat st;
	stat(strPath.c_str(),&st);
	int len = st.st_size;
	//发送http响应
    if(flag==1) sprintf_s(buffer, HEADER1, len);
    else sprintf_s(buffer, HEADER, len);
    if (send(socketClient, buffer, strlen(buffer), 0) < 0)
    {
		printf("Send data failed!");
		closesocket(socketClient);
        return 0;
    }
	size_t size = 0;	
	while (!feof(fp))
	{
		size = fread(buffer, sizeof(char), sizeof(buffer), fp);
		if (send(socketClient, buffer, size, 0) == SOCKET_ERROR)
		{
			wprintf(L"send failed with error: %ld\n", GetLastError());
			closesocket(socketClient);
			return 0;
		}
	}
    closesocket(socketClient);
    return 0;
}