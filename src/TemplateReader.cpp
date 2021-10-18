#include "TemplateReader.h"

#include <fstream>

namespace geology
{

TemplateReader::TemplateReader(const std::string& strTemplateDir)
    : m_strTemplateDir(strTemplateDir)
{

}

std::string TemplateReader::readTemplate(const std::string& strTemplateName)
{
    std::ifstream Stream(m_strTemplateDir + "\\" + strTemplateName);

    if (!Stream.is_open())
        throw std::runtime_error("cant open template");

    std::string strLineBuf;
    std::string strRes;

    while(std::getline(Stream, strLineBuf))
    {
        strRes += strLineBuf + "\n";
    }

    return strRes;
}

} // namespace geology
