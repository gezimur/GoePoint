#include "OrderPage.h"

#include "HTTP_staff.h"

namespace geology
{

std::map<std::string, std::string> make_data_form_map(const httpserver::http_request& crReq)
{
    std::map<std::string, std::string> mArgs;

    mArgs["id"] = crReq.get_arg("id"); ///@todo

    return mArgs;
}

OrderPage::OrderPage(const std::shared_ptr<PageContainer>& spPages, const std::shared_ptr<GeologyDataBase>& spDataBase)
    : IPageProcessor(spPages, spDataBase)
{

}

const std::shared_ptr<httpserver::http_response> OrderPage::getPage(const httpserver::http_request& crReq)
{
    auto strId = crReq.get_cookie("id");
    if (strId.empty())
        return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_spPages->getAuthorizationPage(), 200, "text/html"));

    return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_spPages->getOrderPage(), 200, "text/html"));;
}

const std::shared_ptr<httpserver::http_response> OrderPage::procPostRequest(const httpserver::http_request& crReq)
{
    auto eType = static_cast<DataBaseRequest::data_base_req_type>(get_req_type(crReq));

    auto spReq = DataBaseRequest::make(eType, make_data_form_map(crReq));
    m_spDataBase->pushReq(spReq);

    auto Res = spReq->waitAndGetRes();

    return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(make_json(Res), 200, "text/plain"));
}
} //namespace geology

