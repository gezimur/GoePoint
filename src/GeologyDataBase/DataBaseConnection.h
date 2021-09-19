#pragma once

#include <mutex>
#include <string>
#include <memory>

namespace geology
{

class DataBaseConnection
{
    explicit DataBaseConnection(const std::string& strRequest);

public:
    static std::shared_ptr<DataBaseConnection> make(const std::string& strRequest);

    const std::string& getRequest() const noexcept;

    void setResponce(const std::string& strResponce) noexcept;
    const std::string& getResponce() const noexcept;

private:
    mutable std::mutex m_Mutex;

    std::string m_strRequset;
    std::string m_strResponce;
};

} // namespace geology
