#pragma once

#include <functional>

#include <WinSock2.h>

namespace geology
{

class ServerListenSocket
{
public:
    ServerListenSocket(int iPort);
    ~ServerListenSocket();

    int initializeSocket();
    void stop();

    bool listen();

    SOCKET connect();

private:
    int m_iPort;
    SOCKET m_Socket;
};

} // namespace geology
