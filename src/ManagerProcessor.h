#pragma once

#include <httpserver/http_request.hpp>
#include <httpserver/http_response.hpp>

#include "GeologyDataBase/GeologyDataBase.h"
#include "PageContainer.h"

namespace geology
{

class ManagerProcessor
{
    using responce_type = const std::shared_ptr<httpserver::http_response>;

public:
    explicit ManagerProcessor(const std::shared_ptr<GeologyDataBase>& spDataBase, const std::shared_ptr<PageContainer>& spPages, const std::vector<std::string>& vRegisteredUrl);

    responce_type processGET(const httpserver::http_request& crReq);
    responce_type processPOST(const httpserver::http_request& crReq);

private:
    responce_type procGetOrder(const std::string& strOrderId);

    responce_type procSaveOrder(const httpserver::http_request& crReq, const std::string& strOrderId);

    ManagerProcessor::responce_type saveOrder(const std::map<std::string, std::string>& mOrderArgs);

    ManagerProcessor::responce_type procOrderCustomer(const std::map<std::string, std::string>& mCustumerArgs, bool bRewrite);

    DataBaseResponce findCustomer(const std::map<std::string, std::string>& mCustumerArgs);

    DataBaseResponce addCustomer(const std::map<std::string, std::string>& mCustumerArgs);

    std::shared_ptr<GeologyDataBase> m_spDataBase;

    std::shared_ptr<PageContainer> m_spPages;

    std::vector<std::string> m_vRegisteredUrl;

};

} // namespace geology
