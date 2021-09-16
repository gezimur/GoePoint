#include "DataBaseRequest.h"

namespace geology
{


DataBaseRequest::DataBaseRequest(const std::string& strRequest, responce_func m_fResponce)
    : m_strRequset(strRequest),
      m_fResponce(m_fResponce)
{

}

const std::string& DataBaseRequest::getRequest() const noexcept
{
    return m_strRequset;
}

void DataBaseRequest::sendResponce(const std::string& strResponce)
{
    m_fResponce(strResponce);
}


} // namespace geology
