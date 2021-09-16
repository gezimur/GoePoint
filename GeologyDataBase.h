#pragma once

#include <mutex>
#include <functional>
#include <queue>
#include <thread>

#include <DataBaseRequest.h>

namespace geology
{

class GeologyDataBase
{
    using requset_queue = std::queue<DataBaseRequest>;

public:
    GeologyDataBase();

    void pushReq(const DataBaseRequest& crRequest);

private:
    void threadProc();

    void procNextRequset();

    std::shared_ptr<DataBaseRequest> popRequest();

    std::mutex m_Mutex;
    requset_queue m_qRequest;

    std::thread m_DataBaseThread;
};

} // namespace geology
