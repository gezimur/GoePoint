#include "DataBaseConnection.h"

namespace geology
{


DataBaseConnection::DataBaseConnection(const std::string& strRequest)
    : m_strRequset(strRequest)
{

}

std::shared_ptr<DataBaseConnection> DataBaseConnection::make(const std::string& strRequest)
{
    return std::shared_ptr<DataBaseConnection>(new DataBaseConnection(strRequest));
}

const std::string& DataBaseConnection::getRequest() const noexcept
{
    return m_strRequset;
}

void DataBaseConnection::setResponce(const std::string& strResponce) noexcept
{
    std::lock_guard<std::mutex> Locker(m_Mutex);
    m_strResponce = strResponce;
}

const std::string& DataBaseConnection::getResponce() const noexcept
{
    std::lock_guard<std::mutex> Locker(m_Mutex);
    return m_strResponce;
}

} // namespace geology
