#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll

using namespace std;
int main() {
    //��ʼ�� DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //�����׽���
    SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    //���׽���
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
    sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
    sockAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");  //�����IP��ַ
    sockAddr.sin_port = htons(1234);  //�˿�
    if (SOCKET_ERROR == bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR))) {
        cout << "bind port 1234 error" << endl;
    }
    else {
        cout << "bind port 1234 success" << endl;
    }
    //�������״̬,��󼸸���
    if (SOCKET_ERROR == listen(servSock, 20))
    {
        cout << "listen error" << endl;
    }
    else {
        cout << "listen success" << endl;
    }
    //���տͻ�������
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
            //��ͻ��˷�������
            char msgBuf[] = "liheng";
            send(clntSock, msgBuf, strlen(msgBuf) + sizeof(char), NULL);
        }
        if (0 == strcmp(_recvbuf, "getAge")) {
            //��ͻ��˷�������
            char msgBuf[] = "22";
            send(clntSock, msgBuf, strlen(msgBuf) + sizeof(char), NULL);
        }
        else {
            //��ͻ��˷�������
            char msgBuf[] = "?????";
            send(clntSock, msgBuf, strlen(msgBuf) + sizeof(char), NULL);
        }
    }
    //�ر��׽���
    closesocket(clntSock);
    closesocket(servSock);
    //��ֹ DLL ��ʹ��
    WSACleanup();
    return 0;
}
