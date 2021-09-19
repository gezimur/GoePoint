#include "GeologyServer.h"

#include <iostream>
#include <algorithm>

#include <ws2tcpip.h>

#include "Common/TimeMeter.h"

namespace geology
{

GeologyServer::GeologyServer(int iPort)
    : m_iPort(iPort),
      m_ListenSocket(m_iPort)
{

}

int GeologyServer::start()
{
    if (WSAStartup(MAKEWORD(2, 2), &m_WsaData) == 0)
    {
        printf("WSA Startup succes\n");
    }

    m_ListenSocket.initializeSocket();

    serverProc();

    return 0;
}

void GeologyServer::stop()
{
    WSACleanup();
}

int GeologyServer::getPort() const noexcept
{
    return m_iPort;
}

void GeologyServer::setPort(int iPort) noexcept
{
    m_iPort = iPort;
}

void GeologyServer::serverProc()
{
    auto spDataBaseCtrl = std::make_shared<GeologyDataBase>();

    while (true)
    {
        collectGarbage();

        std::cout << "serverProc() listen" << std::endl;
        if (m_ListenSocket.listen())
        {
            std::cout << "serverProc() add new client " << std::endl;
            m_lClientProcessor.push_back(std::make_shared<ClientProcessor>(m_ListenSocket.connect(), spDataBaseCtrl));
        }

        Sleep(e_sleep_server_msec);
    }

    stop();
}

void GeologyServer::collectGarbage()
{
    m_lClientProcessor.remove_if([](const std::shared_ptr<ClientProcessor>& spClientProcessor)
    {
        return !spClientProcessor->isInitialized();
    });

}

}

