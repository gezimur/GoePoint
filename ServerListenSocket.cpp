#include "ServerListenSocket.h"

#include <memory>

#include <ws2tcpip.h>

#include "TimeMeter.h"

namespace geology
{

const int c_iWorkTime_sec = 20;

struct addrinfo init_hints()
{
    struct addrinfo Hints;
    ZeroMemory(&Hints, sizeof (Hints));
    Hints.ai_family = AF_INET;
    Hints.ai_socktype = SOCK_STREAM;
    Hints.ai_protocol = IPPROTO_TCP;
    Hints.ai_flags = AI_PASSIVE;

    return std::move(Hints);
}

struct addrinfo* get_addr_info(int iPort)
{
    struct addrinfo* pResult = NULL;

    struct addrinfo Hints = init_hints();

    // Resolve the local address and port to be used by the server
    int iResult = getaddrinfo(nullptr, std::to_string(iPort).c_str(), &Hints, &pResult);
    if (iResult != 0)
    {
        WSACleanup();
        return nullptr;
    }

    return std::move(pResult);
}

SOCKET make_listen_socket(std::shared_ptr<addrinfo> spAddrInfo)
{
    SOCKET ListenSocket = INVALID_SOCKET;

    ListenSocket = socket(spAddrInfo->ai_family, spAddrInfo->ai_socktype, spAddrInfo->ai_protocol);
    if (ListenSocket == INVALID_SOCKET)
        return INVALID_SOCKET;

    int iResult = bind( ListenSocket, spAddrInfo->ai_addr, (int)spAddrInfo->ai_addrlen);
    if (iResult == SOCKET_ERROR)
        return INVALID_SOCKET;

    return std::move(ListenSocket);
}

ServerListenSocket::ServerListenSocket(int iPort)
    : m_iPort(iPort),
      m_Socket(INVALID_SOCKET)
{

}

ServerListenSocket::~ServerListenSocket()
{
    stop();
}

int ServerListenSocket::start()
{
    auto spAddrInfo = std::shared_ptr<addrinfo>(get_addr_info(m_iPort), &freeaddrinfo);

    if (!spAddrInfo)
        return 1;

    m_Socket = make_listen_socket(spAddrInfo);

    if (INVALID_SOCKET == m_Socket)
    {
        stop();
        return 1;
    }

    listenProc();

    return 0;
}

void ServerListenSocket::stop()
{
    closesocket(m_Socket);
}

void ServerListenSocket::subscribe(add_client_func fAddClient)
{
    m_fAddClient = fAddClient;
}

void ServerListenSocket::listenProc()
{
    TimeMeter WorkTimeMeter;

    while (WorkTimeMeter.getSecFromStart() < c_iWorkTime_sec)
    {
        if ( listen( m_Socket, SOMAXCONN ) != SOCKET_ERROR )
            procConnection();

        Sleep(e_sleep_server_msec);
    }
}

void ServerListenSocket::procConnection()
{
    auto ClientSocket = accept(m_Socket, nullptr, nullptr);

    if (ClientSocket != INVALID_SOCKET)
        m_fAddClient(std::move(ClientSocket));
}

}

