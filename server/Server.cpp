#include <cstdio>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#define BUF_SIZE 100

int main(){
    WSAData wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serSock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(1234);
    bind(serSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

    listen(serSock, 20);

    SOCKADDR clntAddr;
    int nSize = sizeof(SOCKADDR);
    char buffer[BUF_SIZE] = {0};
    while (1){
        unsigned __int64 clntSock = accept(serSock, (SOCKADDR*)&clntAddr, &nSize);
        int strLen = recv(clntSock, buffer, BUF_SIZE, 0);

        closesocket(clntSock);
        memset(buffer, 0, BUF_SIZE);
    }

    closesocket(serSock);

    WSACleanup();
}