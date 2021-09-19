#pragma once

#include <mutex>
#include <functional>
#include <queue>
#include <thread>

#include "DataBaseConnection.h"

namespace geology
{

class GeologyDataBase
{
    using requset_queue = std::queue<std::shared_ptr<DataBaseConnection>>;

public:
    GeologyDataBase();

    void pushReq(const std::shared_ptr<DataBaseConnection>& spRequest);

private:
    void threadProc();

    void procNextRequset();

    std::shared_ptr<DataBaseConnection> popRequest();

    std::mutex m_Mutex;
    requset_queue m_qRequest;

    std::thread m_DataBaseThread;
};

} // namespace geology
