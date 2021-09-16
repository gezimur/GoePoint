#include "GeologyDataBase.h"

#include <synchapi.h>

namespace geology
{

GeologyDataBase::GeologyDataBase()
    : m_DataBaseThread([this]()
{
    threadProc();
})
{

}

void GeologyDataBase::pushReq(const DataBaseRequest& crRequest)
{
    std::lock_guard<std::mutex> Locker(m_Mutex);
    m_qRequest.push(crRequest);
}

void GeologyDataBase::threadProc()
{
    while (true)
    {
        procNextRequset();

        Sleep(100); // msec
    }
}

void GeologyDataBase::procNextRequset()
{
    auto spRequest = popRequest();
    if (!spRequest)
        return;

    spRequest->sendResponce("Responce processed: ");
}

std::shared_ptr<DataBaseRequest> GeologyDataBase::popRequest()
{
    std::lock_guard<std::mutex> Locker(m_Mutex);
    if (m_qRequest.empty())
        return nullptr;

    auto Request = m_qRequest.front();
    m_qRequest.pop();

    return std::make_shared<DataBaseRequest>(Request);
}

} // namespace geology
