#pragma once

#include <mutex>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <condition_variable>

namespace geology
{

class DataBaseRequest
{
public:
    enum class data_base_req_type
    {
        get_user = 0,
        get_order,
        get_order_list,
        get_customer,
        get_customer_list,
        cnt
    };

private:

    explicit DataBaseRequest(data_base_req_type ReqType, const std::map<std::string, std::string>& mReqArgs);

public:
    static std::shared_ptr<DataBaseRequest> make(data_base_req_type ReqType, const std::map<std::string, std::string>& mReqArgs);

    data_base_req_type getReqType() const noexcept;
    const std::map<std::string, std::string>& getReqArgs() const noexcept;

    void setResMsg(const std::string& strMsg) noexcept;
    void setRes(const std::vector<std::map<std::string, std::string>>& vRes) noexcept;

    const std::string& getResMsg() const noexcept;
    const std::vector<std::map<std::string, std::string>>& getRes() const noexcept;

    const std::string& waitAndGetResMsg() const noexcept;
    const std::vector<std::map<std::string, std::string>>& waitAndGetRes() const noexcept;

private:
    mutable std::mutex m_Mutex;
    mutable std::condition_variable m_ConditionVar;

    data_base_req_type m_ReqType;
    std::map<std::string, std::string> m_mArgs;

    std::string m_strResMsg;
    std::vector<std::map<std::string, std::string>> m_vRes;

};

} // namespace geology
