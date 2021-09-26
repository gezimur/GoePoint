#include "DataBaseConnection.h"

namespace geology
{


DataBaseRequest::DataBaseRequest(data_base_req_type ReqType, const std::map<std::string, std::string>& mReqArgs)
    : m_ReqType(ReqType),
      m_mArgs(mReqArgs)
{

}

std::shared_ptr<DataBaseRequest> DataBaseRequest::make(data_base_req_type ReqType, const std::map<std::string, std::string>& mReqArgs)
{
    return std::shared_ptr<DataBaseRequest>(new DataBaseRequest(ReqType,  mReqArgs));
}

DataBaseRequest::data_base_req_type DataBaseRequest::getReqType() const noexcept
{
    return m_ReqType;
}

const std::map<std::string, std::string>& DataBaseRequest::getReqArgs() const noexcept
{
    return m_mArgs;
}

void DataBaseRequest::setResMsg(const std::string& strMsg) noexcept
{
    std::lock_guard<std::mutex> Locker(m_Mutex);
    m_strResMsg = strMsg;
    m_ConditionVar.notify_one();
}

void DataBaseRequest::setRes(const std::vector<std::map<std::string, std::string>>& vRes) noexcept
{
    std::lock_guard<std::mutex> Locker(m_Mutex);
    m_vRes = vRes;
    m_ConditionVar.notify_one();
}

const std::string& DataBaseRequest::getResMsg() const noexcept
{
    std::lock_guard<std::mutex> Locker(m_Mutex);
    return m_strResMsg;
}

const std::vector<std::map<std::string, std::string>>& DataBaseRequest::getRes() const noexcept
{
    std::lock_guard<std::mutex> Locker(m_Mutex);
    return m_vRes;
}

const std::string& DataBaseRequest::waitAndGetResMsg() const noexcept
{
    std::unique_lock<std::mutex> Lock(m_Mutex);
    m_ConditionVar.wait(Lock, [this]()
    {
        return !m_strResMsg.empty();
    });

    return m_strResMsg;
}

const std::vector<std::map<std::string, std::string>>& DataBaseRequest::waitAndGetRes() const noexcept
{
    std::unique_lock<std::mutex> Lock(m_Mutex);
    m_ConditionVar.wait(Lock, [this]()
    {
        return !m_vRes.empty();
    });

    return m_vRes;
}

} // namespace geology
