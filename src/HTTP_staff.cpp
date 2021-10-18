#include "HTTP_staff.h"

#include <boost/filesystem.hpp>

namespace geology
{

int get_req_type(const httpserver::http_request& crReq)
{
    auto strTypeNum = crReq.get_arg("msg_type");
    if (strTypeNum.empty())
        return -1;

    return std::stoi(strTypeNum);
}

std::string make_json(const std::vector<std::string>& vVal)
{
    std::string strJson;

    strJson += "[";
    for (auto itVal = vVal.begin(); itVal != vVal.end(); ++itVal)
    {
        if (vVal.begin() != itVal)
            strJson += ",";
        strJson += "\"" + *itVal + "\"";
    }
    strJson += "]";

    return strJson;
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

std::map<std::string, std::string> make_order_form_map(const httpserver::http_request& crReq)
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

    return mArgs;
}

std::vector<std::string> make_file_list(const std::string& strDirPath)
{
    std::vector<std::string> vRes;
    for (boost::filesystem::directory_iterator itr(strDirPath); itr!=boost::filesystem::directory_iterator(); ++itr)
        vRes.push_back(itr->path().filename().string());

    return vRes;
}

}
