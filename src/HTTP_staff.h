#pragma once

#include <httpserver.hpp>

#include "DataBaseResponce.h"

namespace geology
{

int get_req_type(const httpserver::http_request& crReq);

std::string make_json(const DataBaseResponce& crResponce);

std::shared_ptr<httpserver::http_response> make_redirect(const std::string& strLocation);

const std::shared_ptr<httpserver::http_response> proc_html_responce(const std::string& strHtml, int iStatus);

const std::shared_ptr<httpserver::http_response> proc_msg_responce(const std::string& strMsg, int iStatus);

const std::shared_ptr<httpserver::http_response> proc_json_responce(const DataBaseResponce& crResp, int iStatus);

const std::shared_ptr<httpserver::http_response> proc_auth_get(const std::string& strPath, const std::string& strAuthPage);

const std::shared_ptr<httpserver::http_response> proc_exit();

const std::shared_ptr<httpserver::http_response> proc_file_responce(const httpserver::http_request& crReq);

std::map<std::string, std::string> make_order_form_map(const httpserver::http_request& crReq);

} // namespace geology
