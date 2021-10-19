#pragma once

#include "TemplateReader.h"

namespace geology
{

class PageContainer
{
public:
    explicit PageContainer(const std::string& strResourcePath);

    const std::string& getAuthorizationPage();

    const std::string& getProfilePage();

    const std::string& getOrderPage();

    const std::string& getOrderListPage();

    const std::string& get404Page();

private:
    void initProfilePages(const std::string& strDataTemplate);
    void initOrderPages(const std::string& strDataTemplate);
    void initOrderListPages(const std::string& strMainTemplate);

    TemplateReader m_Reader;

    std::string m_strAuthorizationPage;

    std::string m_strPofilePage;

    std::string m_strOrderPage;

    std::string m_strOrderListPage;

    std::string m_str404Page;
};

} // namespace geology
