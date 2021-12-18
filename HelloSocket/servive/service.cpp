#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll

using namespace std;
int main() {
    //初始化 DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //创建套接字
    SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    //绑定套接字
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;  //使用IPv4地址
    sockAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");  //具体的IP地址
    sockAddr.sin_port = htons(1234);  //端口
    if (SOCKET_ERROR == bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR))) {
        cout << "bind port 1234 error" << endl;
    }
    else {
        cout << "bind port 1234 success" << endl;
    }
    //进入监听状态,最大几个人
    if (SOCKET_ERROR == listen(servSock, 20))
    {
        cout << "listen error" << endl;
    }
    else {
        cout << "listen success" << endl;
    }
    //接收客户端请求
    sockaddr_in clntAddr = {};
    int nSize = sizeof(sockaddr_in);
    SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
    if (INVALID_SOCKET == clntSock) {
        cout << "accept error" << endl;
    }
    cout << "new usr add: IP :" << inet_ntoa(clntAddr.sin_addr) << endl;

    char _recvbuf[128] = {};
    while (TRUE) {
        int len = recv(clntSock, _recvbuf, 128, 0);
        cout << "date length: "<< len;
        if (len <= 0) {
            cout << "code stop!!" << endl;
            break;
        }
        if (0 == strcmp(_recvbuf, "getName")) {
            //向客户端发送数据
            char msgBuf[] = "liheng";
            send(clntSock, msgBuf, strlen(msgBuf) + sizeof(char), NULL);
        }
        if (0 == strcmp(_recvbuf, "getAge")) {
            //向客户端发送数据
            char msgBuf[] = "22";
            send(clntSock, msgBuf, strlen(msgBuf) + sizeof(char), NULL);
        }
        else {
            //向客户端发送数据
            char msgBuf[] = "?????";
            send(clntSock, msgBuf, strlen(msgBuf) + sizeof(char), NULL);
        }
    }
    //关闭套接字
    closesocket(clntSock);
    closesocket(servSock);
    //终止 DLL 的使用
    WSACleanup();
    return 0;
}
