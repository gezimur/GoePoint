#pragma once

#include <httpserver.hpp>

#include "GeologyDataBase/GeologyDataBase.h"

namespace geology
{

class AuthorizationPage: public httpserver::http_resource
{
public:
    explicit AuthorizationPage(const std::shared_ptr<GeologyDataBase>& spDataBase);

    const std::shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request& /*crReq*/);
    const std::shared_ptr<httpserver::http_response> render_POST(const httpserver::http_request& crReq);

private:
    std::string m_strHTMLTemplate;

    std::shared_ptr<GeologyDataBase> m_spDataBase;
};

} // namespace geology
