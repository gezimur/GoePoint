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
        write_user,

        get_order,
        get_order_greedy,
        write_order,

        get_customer,
        write_customer,

        cnt
    };

private:

    explicit DataBaseRequest(data_base_req_type ReqType, const std::map<std::string, std::string>& mReqArgs);

public:
    static std::shared_ptr<DataBaseRequest> make(data_base_req_type ReqType, const std::map<std::string, std::string>& mReqArgs);

    void setCnt(int iCnt) noexcept;
    void setSortType(const std::string& strSortType) noexcept;

    data_base_req_type getReqType() const noexcept;
    const std::map<std::string, std::string>& getReqArgs() const noexcept;
    int getCnt() const noexcept;
    const std::string& getSortType() const noexcept;

    void setRes(const DataBaseResponce& crResponce) noexcept;

    const DataBaseResponce& getRes() const noexcept;

    const DataBaseResponce& waitAndGetRes() const noexcept;

private:
    mutable std::mutex m_Mutex;
    mutable std::condition_variable m_ConditionVar;

    data_base_req_type m_ReqType;
    std::map<std::string, std::string> m_mArgs;
    int m_iCnt;
    std::string m_strSortType;

    DataBaseResponce m_Res;

};

} // namespace geology
