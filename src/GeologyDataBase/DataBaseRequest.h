#pragma once

#include <mutex>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <condition_variable>

#include "DataBaseResponce.h"

namespace geology
{

class DataBaseRequest
{
public:    
    enum data_base_req_type
    {
        get_user = 0,
        get_user_list,
        write_user,

        get_order,
        get_order_list,
        write_order,

        get_customer,
        get_customer_list,
        write_customer,

        cnt
    };

private:

    explicit DataBaseRequest(data_base_req_type ReqType, const std::map<std::string, std::string>& mReqArgs);

public:
    static std::shared_ptr<DataBaseRequest> make(data_base_req_type ReqType, const std::map<std::string, std::string>& mReqArgs);

    data_base_req_type getReqType() const noexcept;
    const std::map<std::string, std::string>& getReqArgs() const noexcept;

    void setRes(const DataBaseResponce& crResponce) noexcept;

    const DataBaseResponce& getRes() const noexcept;

    const DataBaseResponce& waitAndGetRes() const noexcept;

private:
    mutable std::mutex m_Mutex;
    mutable std::condition_variable m_ConditionVar;

    data_base_req_type m_ReqType;
    std::map<std::string, std::string> m_mArgs;

    DataBaseResponce m_Res;

};

} // namespace geology
