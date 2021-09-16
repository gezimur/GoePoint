#include "ClientSocket.h"

#include <iostream>

#include <ws2tcpip.h>

namespace geology
{

ClientSocket::ClientSocket(const SOCKET& crSocket, requset_func fRequest)
    : m_Socket(std::move(crSocket)),
      m_upMutex(new std::mutex),
      m_fRequest(fRequest)
{

}

//ClientSocket::~ClientSocket()
//{
//    stop();
//}

void ClientSocket::start()
{
    m_upThread.reset(new std::thread([this]()
    {
        threadProc();
    }));
}

void ClientSocket::stop()
{
    closesocket(m_Socket);
    m_Socket = INVALID_SOCKET;
    m_upThread->join();
}

void ClientSocket::threadProc()
{
    while(INVALID_SOCKET != m_Socket)
    {
        procRequest();

        procResponce();

        Sleep(e_thread_sleep_msec);
    }
}

void ClientSocket::procRequest()
{
    int iRequestMsgSize = 256;
    char szRequest[iRequestMsgSize];

    int iReceiveSize = recv(m_Socket, szRequest, iRequestMsgSize, 0);
    if (iReceiveSize <= 0)
        return;

    m_fRequest(DataBaseRequest{szRequest, [this](const std::string& strResponce)
                               {
                                   std::lock_guard<std::mutex> Locker(*m_upMutex);
                                   m_qResponce.push(strResponce);
                               }});
}

void ClientSocket::procResponce()
{
    if (m_qResponce.empty())
        return;

    std::lock_guard<std::mutex> Locker(*m_upMutex);
    auto strResp = m_qResponce.front();
    m_qResponce.pop();
    send(m_Socket, strResp.c_str(), strResp.size(), 0);

}

} // namespace geology
