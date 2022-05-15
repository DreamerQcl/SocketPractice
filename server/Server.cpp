#include <cstdio>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#define BUF_SIZE 100

int main(){
    WSAData wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serSock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &sockAddr.sin_addr);
    sockAddr.sin_port = htons(1234);
    bind(serSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

    listen(serSock, 20);

    SOCKADDR clientAddr{};
    int nSize = sizeof(SOCKADDR);
    char buffer[BUF_SIZE] = {0};
    while (1){
        SOCKET clientSock = accept(serSock, (SOCKADDR*)&clientAddr, &nSize);
        int strLen = recv(clientSock, buffer, BUF_SIZE, 0);

        char *string = "Hello World!";
        send(clientSock, string, strlen(string)+sizeof(char), NULL);

        closesocket(clientSock);
        memset(buffer, 0, BUF_SIZE);
    }

    closesocket(serSock);

    WSACleanup();
}