#pragma once

#include <string>

namespace geology
{

class TemplateReader
{
public:
    TemplateReader(const std::string& strTemplateDir);

    std::string readTemplate(const std::string& strTemplateName);

private:
    std::string m_strTemplateDir;
};

} // namespace geology


