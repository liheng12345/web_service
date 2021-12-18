#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")  //���� ws2_32.dll

using namespace std;
int main() {
    //��ʼ��DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //�����׽���
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == sock) {
        cout << "error build socket" << endl;
    }
    else {
        cout << " build success" << endl;
    }
    //���������������
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
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
        //��������
        char inputBuffer[128] = {};
        cin >> inputBuffer;
        if (strcmp(inputBuffer, "exit") == 0) {
            break;
        }
        else {
           //���������������
            send(sock, inputBuffer, strlen(inputBuffer) + sizeof(char), 0);
        }
        //���շ��������ص�����
        char szBuffer[MAXBYTE] = {};
        int len = recv(sock, szBuffer, MAXBYTE, NULL);
        if (len > 0) {
            //������յ�������
            cout  << szBuffer << endl;
        }
    }
    //�ر��׽���
    closesocket(sock);
    //��ֹʹ�� DLL
    WSACleanup();
    system("pause");
    return 0;
}