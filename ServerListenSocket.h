#pragma once

#include <functional>

#include <WinSock2.h>

namespace geology
{

class ServerListenSocket
{
    using add_client_func = std::function<void(const SOCKET& crClientSocket)>;

    enum
    {
        e_sleep_server_msec = 100
    };

public:
    ServerListenSocket(int iPort);
    ~ServerListenSocket();

    int start();
    void stop();

    void subscribe(add_client_func fAddClient);

private:
    void listenProc();

    void procConnection();

    int m_iPort;
    SOCKET m_Socket;

    add_client_func m_fAddClient;
};

} // namespace geology
