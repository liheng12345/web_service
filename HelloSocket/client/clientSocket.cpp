#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

using namespace std;
int main() {
    //初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //创建套接字
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == sock) {
        cout << "error build socket" << endl;
    }
    else {
        cout << " build success" << endl;
    }
    //向服务器发起请求
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(1234);

    if (SOCKET_ERROR == connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR))) {
        cout << "connect error" << endl;
    }
    else {
        cout << "connect success" << endl;
    }

    while (TRUE) {
        //输入命令
        char inputBuffer[128] = {};
        cin >> inputBuffer;
        if (strcmp(inputBuffer, "exit") == 0) {
            break;
        }
        else {
           //向服务器发送请求
            send(sock, inputBuffer, strlen(inputBuffer) + sizeof(char), 0);
        }
        //接收服务器传回的数据
        char szBuffer[MAXBYTE] = {};
        int len = recv(sock, szBuffer, MAXBYTE, NULL);
        if (len > 0) {
            //输出接收到的数据
            cout  << szBuffer << endl;
        }
    }
    //关闭套接字
    closesocket(sock);
    //终止使用 DLL
    WSACleanup();
    system("pause");
    return 0;
}