#include "CommonProcessor.h"

#include "HTTP_staff.h"

namespace geology
{

std::map<std::string, std::string> make_search_form_map(const httpserver::http_request& crReq)
{
    std::map<std::string, std::string> mArgs;

    auto strArg = crReq.get_arg("work_class");
    if (!strArg.empty())
        mArgs["work_class"] = strArg;

    strArg = crReq.get_arg("work_type");
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

    strArg = crReq.get_arg("ingeneer");
    if (!strArg.empty())
        mArgs["users.full_name"] = strArg;

    strArg = crReq.get_arg("fielder");
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

    return mArgs;
}

CommonProcessor::CommonProcessor(const std::shared_ptr<GeologyDataBase>& spDataBase, const std::shared_ptr<PageContainer>& spPages, const std::vector<std::string>& vRegisteredUrl)
    : m_upDocFiller(make_doc_filler("..\\resources\\doc")),
      m_spDataBase(spDataBase),
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

    if ("/doc_list" == strPath)
        return procDocList(crReq);

    return nullptr;
}

CommonProcessor::responce_type CommonProcessor::procAuthorization(const httpserver::http_request& crReq)
{
    std::map<std::string, std::string> mArgs{{"username", crReq.get_args().at("username")}, {"password", crReq.get_args().at("password")}};

    auto spReq = DataBaseRequest::make(DataBaseRequest::data_base_req_type::get_user, mArgs);
    m_spDataBase->pushReq(spReq);

    auto Res = spReq->waitAndGetRes();

    if ("Nothing found" == Res.getMsg())
        return proc_msg_responce("Authorization failed", 200);

    auto spResp = proc_msg_responce("Success", 200);

    spResp->with_cookie("id", Res.getTable()[0].at("id"));

    return std::move(spResp);
}

CommonProcessor::responce_type CommonProcessor::procOrderList(const httpserver::http_request& crReq)
{
    auto eType = DataBaseRequest::data_base_req_type::get_order_greedy;

    auto spReq = DataBaseRequest::make(eType, make_search_form_map(crReq));
    spReq->setCnt(100);
    m_spDataBase->pushReq(spReq);

    auto Res = spReq->waitAndGetRes();

    return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(make_json(Res), 200, "text/plain"));
}

CommonProcessor::responce_type CommonProcessor::procDocList(const httpserver::http_request& /*crReq*/)
{
    auto vFileList = make_file_list("..\\resources\\doc");

    return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(make_json(vFileList), 200, "text/plain"));
}

CommonProcessor::responce_type CommonProcessor::procDoc(const httpserver::http_request& crReq, const std::string& strFile)
{
    auto vArgs = crReq.get_args();
    std::map<std::string, std::string> mArgs(vArgs.begin(), vArgs.end());
    auto upFiller = geology::make_doc_filler("..\\resources\\doc\\" + strFile);

    upFiller->saveFilledDoc("FilledDoc.docx", mArgs);

    return std::shared_ptr<httpserver::file_response>(new httpserver::file_response("FilledDoc.docx", 200, "application/octet-stream" ));
}

CommonProcessor::responce_type CommonProcessor::procAuthLvl(const httpserver::http_request& crReq)
{
    auto vPath = crReq.get_path_pieces();

    if (2 == vPath.size() && "document" == vPath[0])
            return procDoc(crReq, vPath[1]);

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
