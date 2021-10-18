#include "DataBaseRequest.h"

namespace geology
{

DataBaseRequest::DataBaseRequest(data_base_req_type ReqType, const std::map<std::string, std::string>& mReqArgs)
    : m_ReqType(ReqType),
      m_mArgs(mReqArgs),
      m_iCnt(1)
{

}

std::shared_ptr<DataBaseRequest> DataBaseRequest::make(data_base_req_type ReqType, const std::map<std::string, std::string>& mReqArgs)
{
    return std::shared_ptr<DataBaseRequest>(new DataBaseRequest(ReqType,  mReqArgs));
}

void DataBaseRequest::setCnt(int iCnt) noexcept
{
    m_iCnt = iCnt;
}

void DataBaseRequest::setSortType(const std::string& strSortType) noexcept
{
    m_strSortType = strSortType;
}

DataBaseRequest::data_base_req_type DataBaseRequest::getReqType() const noexcept
{
    return m_ReqType;
}

const std::map<std::string, std::string>& DataBaseRequest::getReqArgs() const noexcept
{
    return m_mArgs;
}

int DataBaseRequest::getCnt() const noexcept
{
    return m_iCnt;
}

const std::string& DataBaseRequest::getSortType() const noexcept
{
    return m_strSortType;
}

void DataBaseRequest::setRes(const DataBaseResponce &crResponce) noexcept
{
    std::lock_guard<std::mutex> Locker(m_Mutex);
    m_Res = crResponce;
    m_ConditionVar.notify_one();
}

const DataBaseResponce &DataBaseRequest::getRes() const noexcept
{
    std::lock_guard<std::mutex> Locker(m_Mutex);
    return m_Res;
}

const DataBaseResponce& DataBaseRequest::waitAndGetRes() const noexcept
{
    std::unique_lock<std::mutex> Lock(m_Mutex);
    m_ConditionVar.wait(Lock, [this]()
    {
        return !m_Res.getMsg().empty() || !m_Res.getTable().empty();
    });

    return m_Res;
}

} // namespace geology
