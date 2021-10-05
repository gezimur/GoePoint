#include "HTTP_staff.h"

namespace geology
{

int get_req_type(const httpserver::http_request& crReq)
{
    auto strTypeNum = crReq.get_arg("msg_type");
    if (strTypeNum.empty())
        return -1;

    return std::stoi(strTypeNum);
}

std::string make_json(const DataBaseResponce& crResponce)
{
    std::string strJson;

    strJson += "{";

    if (!crResponce.getMsg().empty())
        strJson += "\"message\" : \"" + crResponce.getMsg() + "\"";

    const auto& vRows = crResponce.getTable();
    if (vRows.empty())
        return strJson + "}";

    strJson += "\"table\" : [";

    for (auto itRow = vRows.begin(); itRow != vRows.end(); ++itRow)
    {
        if (vRows.begin() != itRow)
            strJson += ",";
        strJson += "{";
        for (auto it = itRow->begin(); it != itRow->end(); ++it)
        {
            if (itRow->begin() != it)
                strJson += ",";
            strJson += "\"" + it->first + "\" : \"" + it->second + "\"";
        }
        strJson += "}";
    }
    strJson += "]";
    strJson += "}";
    return strJson;
}

std::shared_ptr<httpserver::http_response> make_redirect(const std::string& strLocation)
{
    auto spResp = std::shared_ptr<httpserver::http_response>(new httpserver::http_response(302, "text/plain"));

    spResp->with_header("Location", strLocation);

    return spResp;
}

const std::shared_ptr<httpserver::http_response> proc_html_responce(const std::string& strHtml, int iStatus)
{
    return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(strHtml, iStatus, "text/html"));
}

const std::shared_ptr<httpserver::http_response> proc_msg_responce(const std::string& strMsg, int iStatus)
{
    auto strJsonMsg = make_json(DataBaseResponce{strMsg});
    return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(strJsonMsg, iStatus, "text/plain"));
}

const std::shared_ptr<httpserver::http_response> proc_json_responce(const DataBaseResponce& crResp, int iStatus)
{
    auto strJson = make_json(crResp);
    return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(strJson, iStatus, "text/plain"));
}

const std::shared_ptr<httpserver::http_response> proc_auth_get(const std::string& strPath, const std::string& strAuthPage)
{
    if ("/authorization" != strPath)
        return make_redirect("/authorization");

    return proc_html_responce(strAuthPage, 200);
}

const std::shared_ptr<httpserver::http_response> proc_exit()
{
    auto spRes = make_redirect("/authorization");
    spRes->with_cookie("id", "");
    return spRes;
}

}
