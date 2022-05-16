#include <cstdio>
#include <WinSock2.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")

#define BUF_SIZE 100

int main(){
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.S_un.S_addr = inet_addr("127,0,0,1");
    sockAddr.sin_port = htons(1234);

    char buffSend[BUF_SIZE] = {0};
    char buffRecv[BUF_SIZE] = {0};

    while (1){
        SOCKET socket1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        connect(socket1, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

        gets_s(buffSend, BUF_SIZE);
        send(socket1, buffSend, strlen(buffSend), 0);

        recv(socket1, buffRecv, strlen(buffRecv), 0);
        printf(buffRecv);

        memset(buffSend, 0, BUF_SIZE);
        memset(buffRecv, 0, BUF_SIZE);

        closesocket(socket1);
    }

    WSACleanup();

    return 0;
}