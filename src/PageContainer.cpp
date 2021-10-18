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
    strDataTemplate = wrap_in_template(strMainTemplate, strDataTemplate);

    initProfilePages(strDataTemplate);

    initOrderPages(strDataTemplate);

    initOrderListPages(strMainTemplate);

    m_str404Page = wrap_in_template(strMainTemplate, "<h1>Page not found</h1>");
}

const std::string& PageContainer::getAuthorizationPage()
{
    return m_strAuthorizationPage;
}

const std::string& PageContainer::getProfileManagerPage()
{
    return m_strPofileManagerPage;
}

const std::string& PageContainer::getProfileSpecialistPage()
{
    return m_strPofileSpecialistPage;
}

const std::string& PageContainer::getOrderManagerPage()
{
    return m_strOrderManagerPage;
}

const std::string& PageContainer::getOrderSpecialistPage()
{
    return m_strOrderSpecialistPage;
}

const std::string& PageContainer::getOrderListManagerPage()
{
    return m_strOrderListManagerPage;
}

const std::string& PageContainer::getOrderListSpecialistPage()
{
    return m_strOrderListSpecialistPage;
}

const std::string& PageContainer::get404Page()
{
    return m_str404Page;
}

void PageContainer::initProfilePages(const std::string& strDataTemplate)
{
    auto strProfileTemplate = m_Reader.readTemplate("templates\\ProfileTemplate.html");
    strProfileTemplate = wrap_in_template(strDataTemplate, strProfileTemplate);
    strProfileTemplate = wrap_in_template(strProfileTemplate, m_Reader.readTemplate("templates\\ButtonTemplate.html"));

    m_strPofileManagerPage = wrap_in_template(strProfileTemplate, "<script src=\"/resources/profiledata.js\"></script>");
    m_strPofileSpecialistPage = wrap_in_template(strProfileTemplate, "<script src=\"/resources/profiledata.js\"></script>");
}

void PageContainer::initOrderPages(const std::string& strDataTemplate)
{
    auto strOrderTemplate = m_Reader.readTemplate("templates\\OrderTemplate.html");
    strOrderTemplate = wrap_in_template(strDataTemplate, strOrderTemplate);

    m_strOrderManagerPage = wrap_in_template(strOrderTemplate, m_Reader.readTemplate("templates\\ButtonTemplate.html") + "<select id=\"DocList\" value=\"\"></select></br><input id=\"LoadDoc\" class=\"Button\" type=\"submit\" value=\"Скачать документ\" onclick=\"loadDoc()\" />");
    m_strOrderManagerPage = wrap_in_template(m_strOrderManagerPage, "<script src=\"/resources/managerdata.js\"></script>");

    m_strOrderSpecialistPage = wrap_in_template(strOrderTemplate, m_Reader.readTemplate("templates\\ButtonSpecialistTemplate.html") + "<select id=\"DocList\" value=\"\"></select></br><input id=\"LoadDoc\" class=\"Button\" type=\"submit\" value=\"Скачать документ\" onclick=\"loadDoc()\" />");
    m_strOrderSpecialistPage = wrap_in_template(m_strOrderSpecialistPage, "<script src=\"/resources/specialistdata.js\"></script>");
}

void PageContainer::initOrderListPages(const std::string& strMainTemplate)
{
    auto strOrderListTemplate = m_Reader.readTemplate("templates\\OrderListTemplate.html");
    strOrderListTemplate = wrap_in_template(strMainTemplate, strOrderListTemplate);

    m_strOrderListManagerPage = wrap_in_template(strOrderListTemplate, "<a href=\"/order/new\"><input class=\"Button\" type=\"submit\" value=\"Новая заявка\"></a>");
    m_strOrderListManagerPage = wrap_in_template(m_strOrderListManagerPage, "<script src=\"/resources/loadorderlist.js\"></script>");

    m_strOrderListSpecialistPage = wrap_in_template(strOrderListTemplate, "");
    m_strOrderListSpecialistPage = wrap_in_template(m_strOrderListSpecialistPage, "<script src=\"/resources/loadorderlist.js\"></script>");
}

} // namespace geology
