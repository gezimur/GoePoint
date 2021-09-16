#pragma once

#include <functional>
#include <string>

namespace geology
{

class DataBaseRequest
{
    using responce_func = std::function<void(const std::string& strResponce)>;

public:
    DataBaseRequest(const std::string& strRequest, responce_func m_fResponce);

    const std::string& getRequest() const noexcept;

    void sendResponce(const std::string& strResponce);

private:
    responce_func m_fResponce;
    std::string m_strRequset;
};

} // namespace geology
