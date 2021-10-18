#pragma once

#include "TemplateReader.h"

namespace geology
{

class PageContainer
{
public:
    explicit PageContainer(const std::string& strResourcePath);

    const std::string& getAuthorizationPage();

    const std::string& getProfileManagerPage();
    const std::string& getProfileSpecialistPage();

    const std::string& getOrderManagerPage();
    const std::string& getOrderSpecialistPage();

    const std::string& getOrderListManagerPage();
    const std::string& getOrderListSpecialistPage();

    const std::string& get404Page();

private:
    void initProfilePages(const std::string& strDataTemplate);
    void initOrderPages(const std::string& strDataTemplate);
    void initOrderListPages(const std::string& strMainTemplate);

    TemplateReader m_Reader;

    std::string m_strAuthorizationPage;

    std::string m_strPofileManagerPage;
    std::string m_strPofileSpecialistPage;

    std::string m_strOrderManagerPage;
    std::string m_strOrderSpecialistPage;

    std::string m_strOrderListManagerPage;
    std::string m_strOrderListSpecialistPage;

    std::string m_str404Page;
};

} // namespace geology
