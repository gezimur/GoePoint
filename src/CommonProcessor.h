#pragma once

#include <httpserver/http_request.hpp>
#include <httpserver/http_response.hpp>

#include "GeologyDataBase/GeologyDataBase.h"
#include "PageContainer.h"

namespace geology
{

class CommonProcessor
{
    using responce_type = const std::shared_ptr<httpserver::http_response>;

public:
    explicit CommonProcessor(const std::shared_ptr<GeologyDataBase>& spDataBase, const std::shared_ptr<PageContainer>& spPages, const std::vector<std::string>& vRegisteredUrl);

    responce_type processGET(const httpserver::http_request& crReq);
    responce_type processPOST(const httpserver::http_request& crReq);

private:
    CommonProcessor::responce_type procAuthorization(const httpserver::http_request& crReq);

    CommonProcessor::responce_type procOrderList(const httpserver::http_request& crReq);

    responce_type procAuthLvl(const httpserver::http_request& crReq);

    responce_type procCommonLvl(const httpserver::http_request& crReq);

    std::shared_ptr<GeologyDataBase> m_spDataBase;

    std::shared_ptr<PageContainer> m_spPages;

    std::vector<std::string> m_vRegisteredUrl;
};

} // namespace geology
