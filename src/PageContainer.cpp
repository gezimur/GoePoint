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

    auto strMainTemplate = m_Reader.readTemplate("templates\\MainTemplate.html");

    auto strDataTemplate = m_Reader.readTemplate("templates\\DataTemplate.html");

    auto strUserData = m_Reader.readTemplate("templates\\UserData.html");
    m_strPofilePage = wrap_in_template(wrap_in_template(strMainTemplate, strDataTemplate), strUserData);
    m_strPofilePage = wrap_in_template(m_strPofilePage, "<script src=\"/resources/loaddata.js\"></script>");

    auto strOrderData = m_Reader.readTemplate("templates\\OrderData.html");
    m_strOrderPage = wrap_in_template(wrap_in_template(strMainTemplate, strDataTemplate), strOrderData);
    m_strOrderPage = wrap_in_template(m_strOrderPage, "<script src=\"/resources/loaddata.js\"></script>");

    auto strCustomerData = m_Reader.readTemplate("templates\\CustomerData.html");
    m_strCustomerPage = wrap_in_template(wrap_in_template(strMainTemplate, strDataTemplate), strCustomerData);
    m_strCustomerPage = wrap_in_template(m_strCustomerPage, "<script src=\"/resources/loaddata.js\"></script>");

    auto strListTemplate = m_Reader.readTemplate("templates\\ListTemplate.html");

    m_strPofileListPage = wrap_in_template(wrap_in_template(strMainTemplate, strListTemplate), strUserData);
    m_strPofileListPage = wrap_in_template(m_strPofileListPage, "<script src=\"/resources/loadorderlist.js\"></script>");

    m_strOrderListPage = wrap_in_template(wrap_in_template(strMainTemplate, strListTemplate), strOrderData);
    m_strOrderListPage = wrap_in_template(m_strOrderListPage, "<script src=\"/resources/loadorderlist.js\"></script>");

    m_strCustomerListPage = wrap_in_template(wrap_in_template(strMainTemplate, strListTemplate), strCustomerData);
    m_strCustomerListPage = wrap_in_template(m_strCustomerListPage, "<script src=\"/resources/loadorderlist.js\"></script>");

    m_str404Page = wrap_in_template(strMainTemplate, "<h1>Page not found</h1>");
}

const std::string& PageContainer::getAuthorizationPage()
{
    return m_strAuthorizationPage;
}

const std::string& PageContainer::getOrderListPage()
{
    return m_strOrderListPage;
}

const std::string& PageContainer::getCustomerListPage()
{
    return m_strCustomerListPage;
}

const std::string& PageContainer::getUserListPage()
{
    return m_strPofileListPage;
}

const std::string& PageContainer::getOrderPage()
{
    return m_strOrderPage;
}

const std::string& PageContainer::getCustomerPage()
{
    return m_strCustomerPage;
}

const std::string& PageContainer::getUserPage()
{
    return m_strPofilePage;
}

const std::string& PageContainer::get404Page()
{
    return m_str404Page;
}

} // namespace geology
