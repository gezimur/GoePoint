#include "GeologyServer.h"

#include <iostream>
#include <functional>
#include <memory>
#include <list>

#include <ws2tcpip.h>

#include "TimeMeter.h"
#include "ServerListenSocket.h"
#include "ClientSocket.h"

namespace geology
{

const int c_iWorkTime_sec = 20;

GeologyServer::GeologyServer(int iPort)
    : m_iPort(iPort)
{

}

int GeologyServer::start()
{
    if (WSAStartup(MAKEWORD(2, 2), &m_WsaData) == 0)
    {
        printf("WSA Startup succes\n");
    }

    ServerListenSocket ListenSocket(m_iPort);

    auto spDataBaseCtrl = std::make_shared<GeologyDataBase>();
    std::list<ClientSocket> lClientSocket;

    ListenSocket.subscribe([&lClientSocket, &spDataBaseCtrl](const SOCKET& crClientSocket)
    {
        lClientSocket.push_back(ClientSocket{crClientSocket, [&spDataBaseCtrl](const DataBaseRequest& crRequest)
                                             {
                                                 spDataBaseCtrl->pushReq(crRequest);
                                             }});
        lClientSocket.back().start();
    });

    ListenSocket.start();

    stop();

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

}

