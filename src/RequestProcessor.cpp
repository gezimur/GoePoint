#include "RequestProcessor.h"

#include "HTTP_staff.h"

namespace geology
{

std::map<std::string, std::string> make_save_user_form_map(const httpserver::http_request& crReq)
{
    std::map<std::string, std::string> mArgs;

    auto strArg = crReq.get_cookie("id");
    if (!strArg.empty())
        mArgs["id"] = strArg;

    strArg = crReq.get_arg("full_name");
    if (!strArg.empty())
        mArgs["full_name"] = strArg;

    strArg = crReq.get_arg("role");
    if (!strArg.empty())
        mArgs["role"] = strArg;

    strArg = crReq.get_arg("username");
    if (!strArg.empty())
        mArgs["username"] = strArg;

    strArg = crReq.get_arg("password");
    if (!strArg.empty())
        mArgs["password"] = strArg;

    return mArgs;
}

RequestProcessor::RequestProcessor()
    : m_spDataBase(std::make_shared<GeologyDataBase>(geology::ConnectionParams{})), ///@todo make like param
      m_spPages(std::make_shared<PageContainer>("E:\\code\\GeologyServer\\resources")), ///@todo make like param
      m_vRegisteredUrl{"/", "/authorization", "/profile", "/profile/save", "/order_list", "/order", "/exit"},
      m_CommonProcessor(m_spDataBase, m_spPages, m_vRegisteredUrl),
      m_ManagerProcessor(m_spDataBase, m_spPages, m_vRegisteredUrl),
      m_SpecialistProcessor(m_spDataBase, m_spPages, m_vRegisteredUrl)
{

}

RequestProcessor::responce_type RequestProcessor::render_GET(const httpserver::http_request& crReq)
{
    auto spRes = m_CommonProcessor.processGET(crReq);
    if (spRes)
        return spRes;

    return procUserLvl(crReq);
}

RequestProcessor::responce_type RequestProcessor::render_POST(const httpserver::http_request& crReq)
{
    auto spRes = m_CommonProcessor.processPOST(crReq);
    if (spRes)
        return spRes;

    auto spReq = DataBaseRequest::make(DataBaseRequest::data_base_req_type::get_user, {{"id", crReq.get_cookie("id")}});
    m_spDataBase->pushReq(spReq);
    auto Res = spReq->waitAndGetRes();

    if ("Nothing found" == Res.getMsg())
        return proc_exit();

    if ("/profile" == crReq.get_path())
        return proc_json_responce(Res,  200);

    if ("/profile/save" == crReq.get_path())
        return procProfileSave(crReq);

    auto strRole = Res.getTable()[0].at("role");

    if ("0" == strRole) //manager
        return m_ManagerProcessor.processPOST(crReq);
    else if ("1" == strRole) //specialist
        return m_SpecialistProcessor.processPOST(crReq);

    return proc_exit();
}

RequestProcessor::responce_type RequestProcessor::procUserLvl(const httpserver::http_request& crReq)
{
    auto spReq = DataBaseRequest::make(DataBaseRequest::data_base_req_type::get_user, {{"id", crReq.get_cookie("id")}});
    m_spDataBase->pushReq(spReq);
    auto Res = spReq->waitAndGetRes();

    if ("Nothing found" == Res.getMsg())
        return proc_exit();

    if ("/profile" == crReq.get_path())
        return proc_html_responce(m_spPages->getProfileManagerPage(), 200); ///@todo

    auto mUser = Res.getTable()[0];

    return procRoleLvl(crReq, mUser);
}

RequestProcessor::responce_type RequestProcessor::procRoleLvl(const httpserver::http_request& crReq, const std::map<std::string, std::string>& mUser)
{
    auto strRole = mUser.at("role");

    if ("0" == strRole) //manager
        return m_ManagerProcessor.processGET(crReq);
    else if ("1" == strRole) //specialist
        return m_SpecialistProcessor.processGET(crReq);

    return proc_exit(); ///@todo
}

RequestProcessor::responce_type RequestProcessor::procProfileSave(const httpserver::http_request& crReq)
{
    auto spReq = DataBaseRequest::make(DataBaseRequest::data_base_req_type::write_user, make_save_user_form_map(crReq));
    m_spDataBase->pushReq(spReq);
    auto Res = spReq->waitAndGetRes();

    return proc_msg_responce(Res.getMsg(), 200);
}

} //namespace geology
