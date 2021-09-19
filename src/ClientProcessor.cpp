#include "ClientProcessor.h"

#include <iostream>

#include <ws2tcpip.h>

namespace geology
{

ClientProcessor::ClientProcessor(const SOCKET& crSocket, std::shared_ptr<GeologyDataBase> spDataBaseCtr)
    : m_Socket(std::move(crSocket)),
      m_bRunning(true), // debug
      m_spGeologyDataBase(spDataBaseCtr),
      m_Thread([this]()
{
    threadProc();
})
{

}

bool ClientProcessor::isInitialized()
{
    return m_bRunning;
}

void ClientProcessor::stop()
{
//    std::cout << "stop client" << std::endl;

    shutdown(m_Socket, SD_SEND);
    closesocket(m_Socket);

    m_bRunning = false;

//    std::cout << "stop client complite" << std::endl;
}

void ClientProcessor::threadProc()
{
    bool bRun = true;
    while(bRun && INVALID_SOCKET != m_Socket)
    {
        bRun = procRequest();

        if (bRun)
            bRun &= procResponce();

        if (bRun)
            Sleep(e_thread_sleep_msec);
    }

    stop();
}

bool ClientProcessor::procRequest()
{
    int iRequestMsgSize = 256;
    char szRequest[iRequestMsgSize];

    int iReceiveSize = recv(m_Socket, szRequest, iRequestMsgSize, 0);

    if (iReceiveSize <= 0)
        return false;

//    std::cout << "Request: " << szRequest << std::endl;

    m_qConnection.push(DataBaseConnection::make(szRequest));
    m_spGeologyDataBase->pushReq(m_qConnection.front());

    return true;
}

bool ClientProcessor::procResponce()
{
    if (m_qConnection.empty())
        return true;

    auto strResp = m_qConnection.front()->getResponce();

    if (strResp.empty())
        return true;

    m_qConnection.pop();

//    std::cout << "Responce: " << strResp << std::endl;

    return send(m_Socket, strResp.c_str(), strResp.size(), 0) >= 0;
}

} // namespace geology
