#pragma once

#include <httpserver/http_resource.hpp>

#include "CommonProcessor.h"
#include "UserProcessor.h"
#include "SpecialistProcessor.h"

namespace geology
{

class RequestProcessor: public httpserver::http_resource
{
    using responce_type = const std::shared_ptr<httpserver::http_response>;

public:
    RequestProcessor();

    responce_type render_GET(const httpserver::http_request& crReq);
    responce_type render_POST(const httpserver::http_request& crReq);

private:
    responce_type procUserLvl(const httpserver::http_request& crReq);

    responce_type procProfileSave(const httpserver::http_request& crReq);

    std::shared_ptr<GeologyDataBase> m_spDataBase;

    std::shared_ptr<PageContainer> m_spPages;

    std::vector<std::string> m_vRegisteredUrl;

    CommonProcessor m_CommonProcessor;
    UserProcessor m_UserProcessor;
};

} // namespace geology
