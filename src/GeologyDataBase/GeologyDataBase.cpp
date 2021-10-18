#include "GeologyDataBase.h"

#include <windows.h>

namespace geology
{

GeologyDataBase::GeologyDataBase(const ConnectionParams& crParams)
    : m_upDataBaseCtrl(make_ctrl(crParams)),
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
        return procLoadList(IDataBaseCtrl::e_user, spRequest);

    case DataBaseRequest::data_base_req_type::write_user :
        return procWrite(IDataBaseCtrl::e_user, spRequest);

    case DataBaseRequest::data_base_req_type::get_order :
        return procLoadList(IDataBaseCtrl::e_order, spRequest);

    case DataBaseRequest::data_base_req_type::get_order_greedy :
        return procLoadOrderGreedy(spRequest);

    case DataBaseRequest::data_base_req_type::write_order :
        return procWrite(IDataBaseCtrl::e_order, spRequest);

    case DataBaseRequest::data_base_req_type::get_customer :
        return procLoadList(IDataBaseCtrl::e_customer, spRequest);

    case DataBaseRequest::data_base_req_type::write_customer :
        return procWrite(IDataBaseCtrl::e_customer, spRequest);

    default:
    {
        spRequest->setRes(DataBaseResponce{"invalid request"});
    }
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
