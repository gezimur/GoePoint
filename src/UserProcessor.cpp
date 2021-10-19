#include "UserProcessor.h"

#include  "HTTP_staff.h"

namespace geology
{

bool is_equals(const std::map<std::string, std::string>& mLeft, const std::map<std::string, std::string>& mRight)
{
    return std::all_of(mLeft.begin(), mLeft.end(), [&mRight](const std::pair<std::string, std::string>& prLeft)
    {
        auto itRight = mRight.find(prLeft.first);
        return mRight.end() != itRight && prLeft.second == itRight->second;
    });
}

std::map<std::string, std::string> make_customer_args(const httpserver::http_request& crReq)
{
    std::map<std::string, std::string> mArgs;

    auto strArg = crReq.get_arg("customer");
    if (!strArg.empty())
        mArgs["full_name"] = strArg;

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

UserProcessor::UserProcessor(const std::shared_ptr<GeologyDataBase>& spDataBase, const std::shared_ptr<PageContainer>& spPages, const std::vector<std::string>& vRegisteredUrl)
    : m_spDataBase(spDataBase),
      m_spPages(spPages),
      m_vRegisteredUrl(vRegisteredUrl)
{

}

UserProcessor::responce_type UserProcessor::processGET(const httpserver::http_request& crReq)
{
    auto strPath = crReq.get_path();

    if ("/order_list" == strPath)
        return proc_html_responce(m_spPages->getOrderListPage(), 200);

    if (std::string::npos == strPath.find("/order"))
        return proc_html_responce(m_spPages->get404Page(), 200);

    return proc_html_responce(m_spPages->getOrderPage(), 200);
}

UserProcessor::responce_type UserProcessor::processPOST(const httpserver::http_request& crReq)
{
    auto vPath = crReq.get_path_pieces();

    if ("order" != vPath[0])
        return proc_msg_responce("Unknow request", 200);

    if (2 == vPath.size())
        return procGetOrder(vPath[1]);
    if (3 == vPath.size())
        return procSaveOrder(crReq, vPath[1]);

    return proc_msg_responce("Invalid request", 200);
}

UserProcessor::responce_type UserProcessor::procGetOrder(const std::string& strOrderId)
{
    DataBaseResponce Res;

    if ("new" != strOrderId)
    {
        auto spReq = DataBaseRequest::make(DataBaseRequest::data_base_req_type::get_order_greedy, {{"orders.id", strOrderId}});
        m_spDataBase->pushReq(spReq);

        Res = spReq->waitAndGetRes();
    }

    return proc_json_responce(Res, 200);
}

UserProcessor::responce_type UserProcessor::procSaveOrder(const httpserver::http_request& crReq, const std::string& strOrderId)
{
    auto  mCustumerArgs = make_customer_args(crReq);

    auto spRes = procOrderCustomer(mCustumerArgs, crReq.get_arg("rewrite_customer").empty());
    if (spRes)
        return spRes;

    auto mOrderArgs = make_order_form_map(crReq);

    mOrderArgs["customer"] = mCustumerArgs["passport_number"];
    if ("new" != strOrderId)
        mOrderArgs["id"] = strOrderId;

    return saveOrder(mOrderArgs);
}

UserProcessor::responce_type UserProcessor::saveOrder(const std::map<std::string, std::string>& mOrderArgs)
{
    auto eReqType = DataBaseRequest::data_base_req_type::write_order;

    auto spReq = DataBaseRequest::make(eReqType, mOrderArgs); ///@todo
    m_spDataBase->pushReq(spReq);

    auto Res = spReq->waitAndGetRes();

    return proc_json_responce(Res, 200);
}

UserProcessor::responce_type UserProcessor::procOrderCustomer(const std::map<std::string, std::string>& mCustumerArgs, bool bRewrite)
{
    auto FindCustomerRes = findCustomer({{"passport_number", mCustumerArgs.at("passport_number")}});

    if (FindCustomerRes.getTable().empty() && "Nothing found" != FindCustomerRes.getMsg())
        return proc_msg_responce(FindCustomerRes.getMsg(), 200);

    if ("Nothing found" == FindCustomerRes.getMsg())
    {
        auto AddCustomerRes = addCustomer(mCustumerArgs);
        if ("Success" != AddCustomerRes.getMsg())
            return proc_msg_responce(AddCustomerRes.getMsg(), 200);
    }
    else
    {
        if (!is_equals(mCustumerArgs, FindCustomerRes.getTable()[0]))
        {
            if (bRewrite)
                return proc_msg_responce("rewrite_customer?", 200);
            else
                addCustomer(mCustumerArgs);
        }
    }

    return nullptr;
}

DataBaseResponce UserProcessor::findCustomer(const std::map<std::string, std::string>& mCustumerArgs)
{
    auto spReq = DataBaseRequest::make(DataBaseRequest::data_base_req_type::get_customer, mCustumerArgs); ///@todo
    m_spDataBase->pushReq(spReq);

    return spReq->waitAndGetRes();
}

DataBaseResponce UserProcessor::addCustomer(const std::map<std::string, std::string>& mCustumerArgs)
{
    auto spReq = DataBaseRequest::make(DataBaseRequest::data_base_req_type::write_customer, mCustumerArgs); ///@todo
    m_spDataBase->pushReq(spReq);

    return spReq->waitAndGetRes();
}

} // namespace geology
