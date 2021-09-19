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

void GeologyDataBase::pushReq(const std::shared_ptr<DataBaseConnection>& spRequest)
{
    std::lock_guard<std::mutex> Locker(m_Mutex);
    m_qRequest.push(spRequest);
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

    spRequest->setResponce("Responce processed: ");
}

std::shared_ptr<DataBaseConnection> GeologyDataBase::popRequest()
{
    std::lock_guard<std::mutex> Locker(m_Mutex);
    if (m_qRequest.empty())
        return nullptr;

    auto spRequest = m_qRequest.front();
    m_qRequest.pop();

    return spRequest;
}

} // namespace geology
