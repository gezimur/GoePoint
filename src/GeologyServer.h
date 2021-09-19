#pragma once

#include <list>
#include <memory>

#include <WinSock2.h>

#include "ServerListenSocket.h"
#include "ClientProcessor.h"

namespace geology
{

class GeologyServer
{
    enum
    {
        e_sleep_server_msec = 10
    };

public:
    GeologyServer(int iPort);

    int start();
    void stop();

    int getPort() const noexcept;
    void setPort(int iPort) noexcept;

private:
    void serverProc();

    void collectGarbage();

    int m_iPort;

    std::list<std::shared_ptr<ClientProcessor>> m_lClientProcessor;

    ServerListenSocket m_ListenSocket;

    WSADATA m_WsaData;

};

} // namespace geology
