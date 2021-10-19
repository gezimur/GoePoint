#include "PageContainer.h"

#include <exception>

namespace geology
{

std::string wrap_in_template(const std::string& strTemplate, const std::string& strVal)
{
    auto lluPlace = strTemplate.find('$');
    if (std::string::npos == lluPlace)
        return "";

    std::string strRes;

    strRes.insert(strRes.begin(), strTemplate.begin(), strTemplate.begin() + lluPlace);
    strRes.insert(strRes.end(), strVal.begin(), strVal.end());

    ++lluPlace;
    strRes.insert(strRes.end(), strTemplate.begin() + lluPlace, strTemplate.end());

    return strRes;
}

PageContainer::PageContainer(const std::string& strResourcePath)
    : m_Reader(strResourcePath)
{
    m_strAuthorizationPage = m_Reader.readTemplate("templates\\Authorization.html");

    m_strPofilePage = m_Reader.readTemplate("templates\\ProfilePage.html");

    m_strOrderPage = m_Reader.readTemplate("templates\\OrderPage.html");

    m_strOrderListPage = m_Reader.readTemplate("templates\\OrderListPage.html");

    auto strMainTemplate = m_Reader.readTemplate("templates\\MainTemplate.html");
    m_str404Page = wrap_in_template(strMainTemplate, "<h1>Page not found</h1>");
}

const std::string& PageContainer::getAuthorizationPage()
{
    return m_strAuthorizationPage;
}

const std::string& PageContainer::getProfilePage()
{
    return m_strPofilePage;
}

const std::string& PageContainer::getOrderPage()
{
    return m_strOrderPage;
}

const std::string& PageContainer::getOrderListPage()
{
    return m_strOrderListPage;
}

const std::string& PageContainer::get404Page()
{
    return m_str404Page;
}

} // namespace geology
