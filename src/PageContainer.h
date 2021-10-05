#pragma once

#include "TemplateReader.h"

namespace geology
{

class PageContainer
{
public:
    explicit PageContainer(const std::string& strResourcePath);

    const std::string& getAuthorizationPage();

    const std::string& getOrderListPage();
    const std::string& getCustomerListPage();
    const std::string& getUserListPage();

    const std::string& getOrderPage();
    const std::string& getCustomerPage();
    const std::string& getUserPage();

    const std::string& get404Page();

private:
    TemplateReader m_Reader;

    std::string m_strAuthorizationPage;

    std::string m_strPofilePage;
    std::string m_strOrderPage;
    std::string m_strCustomerPage;

    std::string m_strPofileListPage;
    std::string m_strOrderListPage;
    std::string m_strCustomerListPage;

    std::string m_str404Page;
};

} // namespace geology
