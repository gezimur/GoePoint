#include <iostream>
#include <thread>

#include <ws2tcpip.h>

#include "GeologyServer.h"
#include "TimeMeter.h"

void send_proc(int iPort)
{

    addrinfo *result = NULL, *ptr = NULL, hints;

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int iResult = getaddrinfo("127.0.0.1", std::to_string(iPort).c_str(), &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        throw std::runtime_error("getaddrinfo failed");
    }

    SOCKET Socket = INVALID_SOCKET;

    ptr=result;

    Socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (Socket == INVALID_SOCKET) {
        throw std::runtime_error("Error at socket(): " + std::to_string( WSAGetLastError()));
        freeaddrinfo(result);
        WSACleanup();
    }

    iResult = connect( Socket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        closesocket(Socket);
        Socket = INVALID_SOCKET;
        throw std::runtime_error("connection failed");
    }

    geology::TimeMeter ClientTimeMeter;

    try
    {

    while (ClientTimeMeter.getSecFromStart() < 20)
    {
        std::string strMsg("Client already works for: " + std::to_string(ClientTimeMeter.getSecFromStart()) + "sec");
        int iSendSize = send(Socket, strMsg.c_str(), strMsg.size(), 0);
        if (iSendSize > 0)
            std::cout << "Send: " << strMsg << std::endl;


        int iMsgSize = 256;
        char szMsg[iMsgSize];
        int iRecvSize = recv(Socket, szMsg, iMsgSize, 0);
        if (iRecvSize > 0)
            std::cout << "Recive: " << szMsg << std::endl;

        Sleep(200);
    }
    }
    catch(std::system_error& rExc)
    {
        int a ;
        std::cout << "TestClient: " << rExc.what() << std::endl;
    }
}

int main()
{
    try
    {
        int iPort = 2345;

        geology::GeologyServer Server(iPort);

        std::thread ClientThread([](int iPort)
        {
            Sleep(500);

            send_proc(iPort);

        }, iPort);

        Server.start();

        ClientThread.join();

        return 0;
    }
    catch (std::runtime_error& rExc)
    {
        std::cout << rExc.what() << std::endl;
        return 1;
    }
    catch(std::system_error& rExc)
    {
        int a ;
        std::cout << "TestClient: " << rExc.what() << std::endl;
    }
}
