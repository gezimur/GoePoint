#pragma once

#include <mutex>
#include <thread>
#include <functional>

#include <WinSock2.h>

#include "GeologyDataBase.h"

namespace geology
{

class ClientSocket
{
    using requset_func = std::function<void(const DataBaseRequest&)>;

    enum
    {
        e_thread_sleep_msec = 10
    };

public:
    explicit ClientSocket(const SOCKET& crSocket, requset_func fRequest);

//    ~ClientSocket();

    void start();
    void stop();

private:
    void threadProc();

    void procRequest();

    void procResponce();

    SOCKET m_Socket;

    std::unique_ptr<std::mutex> m_upMutex;

    requset_func m_fRequest;

    std::queue<std::string> m_qResponce;

    std::unique_ptr<std::thread> m_upThread;
};

} // namespace geology
