#include "AuthorizationPage.h"

#include "TemplateReader.h"

namespace geology
{

AuthorizationPage::AuthorizationPage(const std::shared_ptr<GeologyDataBase>& spDataBase)
    : m_spDataBase(spDataBase)
{
    TemplateReader Reader("E:\\code\\GeologyServer\\templates");

    m_strHTMLTemplate = Reader.readTemplate("Authorization.html");
}

const std::shared_ptr<httpserver::http_response> AuthorizationPage::render_GET(const httpserver::http_request& /*crReq*/)
{
    return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_strHTMLTemplate, 200, "text/html"));
}

const std::shared_ptr<httpserver::http_response> AuthorizationPage::render_POST(const httpserver::http_request& crReq)
{
    std::map<std::string, std::string> mArgs;
    mArgs.insert(crReq.get_args().begin(), crReq.get_args().end());

    auto spReq = DataBaseRequest::make(DataBaseRequest::data_base_req_type::get_user, mArgs);
    m_spDataBase->pushReq(spReq);

    auto strResp = spReq->getResMsg();

    return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(strResp, 200, "text/plain"));
}

} //namespace geology

