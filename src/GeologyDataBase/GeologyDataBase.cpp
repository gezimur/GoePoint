#include "GeologyDataBase.h"

#include <synchapi.h>

namespace geology
{

GeologyDataBase::GeologyDataBase(const PGConnection& crConnection)
    : m_DataBaseCtrl(crConnection),
      m_DataBaseThread([this]()
{
    threadProc();
})
{

}

void GeologyDataBase::pushReq(const std::shared_ptr<DataBaseRequest>& spRequest)
{
    std::lock_guard<std::mutex> Locker(m_Mutex);
    m_qRequest.push(spRequest);
}

void GeologyDataBase::threadProc()
{
    while (true)
    {
        procNextRequest();

        Sleep(100); // msec
    }
}

void GeologyDataBase::procNextRequest()
{
    auto spRequest = popRequest();
    if (!spRequest)
        return;

    auto ReqType = spRequest->getReqType();

    switch (ReqType)
    {
    case DataBaseRequest::data_base_req_type::get_user :
    {
        procLoadSingle<User>(spRequest);
        break;
    }
    case DataBaseRequest::data_base_req_type::get_order :
    {
        procLoadSingle<Order>(spRequest);
        break;
    }
    case DataBaseRequest::data_base_req_type::get_order_list :
    {
        procLoadList<Order>(spRequest);
        break;
    }
    case DataBaseRequest::data_base_req_type::get_customer :
    {
        procLoadSingle<Customer>(spRequest);
        break;
    }
    case DataBaseRequest::data_base_req_type::get_customer_list :
    {
        procLoadList<Customer>(spRequest);
        break;
    }
    default:
        break;
    }
}

std::shared_ptr<DataBaseRequest> GeologyDataBase::popRequest()
{
    std::lock_guard<std::mutex> Locker(m_Mutex);
    if (m_qRequest.empty())
        return nullptr;

    auto spRequest = m_qRequest.front();
    m_qRequest.pop();

    return spRequest;
}

} // namespace geology
