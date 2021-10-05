#include "ManagerProcessor.h"

#include  "HTTP_staff.h"

namespace geology
{

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

ManagerProcessor::ManagerProcessor(const std::shared_ptr<GeologyDataBase>& spDataBase, const std::shared_ptr<PageContainer>& spPages, const std::vector<std::string>& vRegisteredUrl)
    : m_spDataBase(spDataBase),
      m_spPages(spPages),
      m_vRegisteredUrl(vRegisteredUrl)
{

}

ManagerProcessor::responce_type ManagerProcessor::processGET(const httpserver::http_request& crReq)
{
    auto strPath = crReq.get_path();

    if ("/order_list" == strPath)
        return proc_html_responce(m_spPages->getOrderListManagerPage(), 200); ///@todo manager page

    if (std::string::npos == strPath.find("/order"))
        return proc_html_responce(m_spPages->get404Page(), 200);

    return proc_html_responce(m_spPages->getOrderManagerPage(), 200); ///@todo manager page
}

ManagerProcessor::responce_type ManagerProcessor::processPOST(const httpserver::http_request& crReq)
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

ManagerProcessor::responce_type ManagerProcessor::procGetOrder(const std::string& strOrderId)
{
    DataBaseResponce Res;

    if ("new" != strOrderId)
    {
        auto spReq = DataBaseRequest::make(DataBaseRequest::data_base_req_type::get_order, {{"orders.id", strOrderId}});
        m_spDataBase->pushReq(spReq);

        Res = spReq->waitAndGetRes();
    }

    return proc_json_responce(Res, 200);
}

ManagerProcessor::responce_type ManagerProcessor::procSaveOrder(const httpserver::http_request& crReq, const std::string& strOrderId)
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

ManagerProcessor::responce_type ManagerProcessor::saveOrder(const std::map<std::string, std::string>& mOrderArgs)
{
    auto eReqType = DataBaseRequest::data_base_req_type::write_order;

    auto spReq = DataBaseRequest::make(eReqType, mOrderArgs); ///@todo
    m_spDataBase->pushReq(spReq);

    auto Res = spReq->waitAndGetRes();

    return proc_json_responce(Res, 200);
}

ManagerProcessor::responce_type ManagerProcessor::procOrderCustomer(const std::map<std::string, std::string>& mCustumerArgs, bool bRewrite)
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
        if (FindCustomerRes.getTable()[0] != mCustumerArgs)
        {
            if (bRewrite)
                return proc_msg_responce("rewrite_customer?", 200);
            else
                addCustomer(mCustumerArgs);
        }
    }

    return nullptr;
}

DataBaseResponce ManagerProcessor::findCustomer(const std::map<std::string, std::string>& mCustumerArgs)
{
    auto spReq = DataBaseRequest::make(DataBaseRequest::data_base_req_type::get_customer_list, mCustumerArgs); ///@todo
    m_spDataBase->pushReq(spReq);

    return spReq->waitAndGetRes();
}

DataBaseResponce ManagerProcessor::addCustomer(const std::map<std::string, std::string>& mCustumerArgs)
{
    auto spReq = DataBaseRequest::make(DataBaseRequest::data_base_req_type::write_customer, mCustumerArgs); ///@todo
    m_spDataBase->pushReq(spReq);

    return spReq->waitAndGetRes();
}

} // namespace geology
