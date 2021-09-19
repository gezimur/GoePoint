#pragma once

#include <atomic>
#include <thread>
#include <functional>

#include <WinSock2.h>

#include "GeologyDataBase/GeologyDataBase.h"
#include "Common/ThreadContainer.h"

namespace geology
{

class ClientProcessor
{
    enum
    {
        e_thread_sleep_msec = 10
    };

public:
    explicit ClientProcessor(const SOCKET& crSocket, std::shared_ptr<GeologyDataBase> spDataBaseCtr);

    bool isInitialized();

private:
    void stop();

    void threadProc();

    bool procRequest();

    bool procResponce();

    SOCKET m_Socket;

    std::atomic_bool m_bRunning;

    std::shared_ptr<GeologyDataBase> m_spGeologyDataBase;

    std::queue<std::shared_ptr<DataBaseConnection>> m_qConnection;

//    std::thread m_Thread;
    ThreadContainer m_Thread;
};

} // namespace geology
