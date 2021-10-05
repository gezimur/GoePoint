#include "CommonProcessor.h"

#include "HTTP_staff.h"

namespace geology
{

std::map<std::string, std::string> make_search_form_map(const httpserver::http_request& crReq)
{
    std::map<std::string, std::string> mArgs;

    auto strArg = crReq.get_arg("work_type");
    if (!strArg.empty())
        mArgs["work_type"] = strArg;

    strArg = crReq.get_arg("order_date");
    if (!strArg.empty())
        mArgs["order_date"] = strArg;

    strArg = crReq.get_arg("deadline");
    if (!strArg.empty())
        mArgs["deadline"] = strArg;

    strArg = crReq.get_arg("place");
    if (!strArg.empty())
        mArgs["place"] = strArg;

    strArg = crReq.get_arg("status");
    if (!strArg.empty())
        mArgs["status"] = strArg;

    strArg = crReq.get_arg("executor");
    if (!strArg.empty())
        mArgs["users.full_name"] = strArg;

    strArg = crReq.get_arg("customer");
    if (!strArg.empty())
        mArgs["customer.full_name"] = strArg;

    strArg = crReq.get_arg("passport_number");
    if (!strArg.empty())
        mArgs["passport_number"] = strArg;

    strArg = crReq.get_arg("passport_gived");
    if (!strArg.empty())
        mArgs["passport_gived"] = strArg;

    strArg = crReq.get_arg("passport_date");
    if (!strArg.empty())
        mArgs["passport_date"] = strArg;

    strArg = crReq.get_arg("snils");
    if (!strArg.empty())
        mArgs["snils"] = strArg;

    strArg = crReq.get_arg("phone");
    if (!strArg.empty())
        mArgs["phone"] = strArg;

    strArg = crReq.get_arg("email");
    if (!strArg.empty())
        mArgs["email"] = strArg;

    mArgs["cnt"] = "100";
    return mArgs;
}

CommonProcessor::CommonProcessor(const std::shared_ptr<GeologyDataBase>& spDataBase, const std::shared_ptr<PageContainer>& spPages, const std::vector<std::string>& vRegisteredUrl)
    : m_spDataBase(spDataBase),
      m_spPages(spPages),
      m_vRegisteredUrl(vRegisteredUrl)
{

}

CommonProcessor::responce_type CommonProcessor::processGET(const httpserver::http_request& crReq)
{
    return procAuthLvl(crReq);
}

CommonProcessor::responce_type CommonProcessor::processPOST(const httpserver::http_request& crReq)
{
    auto strPath = crReq.get_path();

    if (crReq.get_cookie("id").empty())
    {
        if ("/authorization" == strPath)
            return procAuthorization(crReq);

        return proc_msg_responce("Authorization failed", 200);
    }

    if ("/order_list" == strPath)
        return procOrderList(crReq);

    return nullptr;
}

CommonProcessor::responce_type CommonProcessor::procAuthorization(const httpserver::http_request& crReq)
{
    std::map<std::string, std::string> mArgs{{"username", crReq.get_args().at("username")}, {"password", crReq.get_args().at("password")}};

    auto spReq = DataBaseRequest::make(DataBaseRequest::data_base_req_type::get_user_list, mArgs);
    m_spDataBase->pushReq(spReq);

    auto Res = spReq->waitAndGetRes();

    if ("Nothing found" == Res.getMsg())
        return proc_msg_responce("Authorization failed", 200);

    auto spResp = make_redirect("/profile");

    spResp->with_cookie("id", Res.getTable()[0].at("id"));

    return std::move(spResp);
}

CommonProcessor::responce_type CommonProcessor::procOrderList(const httpserver::http_request& crReq)
{
    auto eType = DataBaseRequest::data_base_req_type::get_order_list;

    auto spReq = DataBaseRequest::make(eType, make_search_form_map(crReq));
    m_spDataBase->pushReq(spReq);

    auto Res = spReq->waitAndGetRes();

    return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(make_json(Res), 200, "text/plain"));
}

CommonProcessor::responce_type CommonProcessor::procAuthLvl(const httpserver::http_request& crReq)
{
    if (crReq.get_cookie("id").empty())
        return proc_auth_get(crReq.get_path(), m_spPages->getAuthorizationPage());
    else
        return procCommonLvl(crReq);
}

CommonProcessor::responce_type CommonProcessor::procCommonLvl(const httpserver::http_request& crReq)
{
    auto strPath = crReq.get_path();

    if ("/" == strPath) // id not empty check it upper level
        return make_redirect("/profile");
    else if ("/authorization" == strPath) // id not empty check it upper level
        return make_redirect("/profile");
    else if ("/exit" == strPath)
        return proc_exit();

    return nullptr;
}

} // namespace geology
