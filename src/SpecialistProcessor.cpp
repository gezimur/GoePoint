#include "SpecialistProcessor.h"

#include <assert.h>

#include  "HTTP_staff.h"


namespace geology
{

SpecialistProcessor::SpecialistProcessor(const std::shared_ptr<GeologyDataBase>& spDataBase, const std::shared_ptr<PageContainer>& spPages, const std::vector<std::string>& vRegisteredUrl)
    : m_spDataBase(spDataBase),
      m_spPages(spPages),
      m_vRegisteredUrl(vRegisteredUrl)
{

}

SpecialistProcessor::responce_type SpecialistProcessor::processGET(const httpserver::http_request& crReq)
{
    auto strPath = crReq.get_path();

    if ("/order_list" == strPath)
        return proc_html_responce(m_spPages->getOrderListSpecialistPage(), 200); ///@todo manager page

    if (std::string::npos == strPath.find("/order"))
        return proc_exit(); ///@todo exception page

    return proc_html_responce(m_spPages->getOrderSpecialistPage(), 200); ///@todo manager page
}

SpecialistProcessor::responce_type SpecialistProcessor::processPOST(const httpserver::http_request& crReq)
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

SpecialistProcessor::responce_type SpecialistProcessor::procGetOrder(const std::string& strOrderId)
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

SpecialistProcessor::responce_type SpecialistProcessor::procSaveOrder(const httpserver::http_request& crReq, const std::string& strOrderId)
{
    auto Order = loadOrder(strOrderId);

    assert(!Order.getTable().empty());

    if (!Order.getTable()[0].at("executor").empty() && Order.getTable()[0].at("executor") != crReq.get_cookie("id"))
        return proc_msg_responce("You can't do this", 200);

    auto Res = changeOrder(crReq, Order);

    return proc_json_responce(Res, 200);
}

DataBaseResponce SpecialistProcessor::loadOrder(const std::string& strOrderId)
{
    auto eReqType = DataBaseRequest::data_base_req_type::get_order;

    auto spReq = DataBaseRequest::make(eReqType, {{"id", strOrderId}});
    m_spDataBase->pushReq(spReq);

    return spReq->waitAndGetRes();
}

DataBaseResponce SpecialistProcessor::changeOrder(const httpserver::http_request& crReq, const DataBaseResponce& crOrder)
{
    std::map<std::string, std::string> mArgs(crOrder.getTable()[0].begin(), crOrder.getTable()[0].end()); ///@todo
    mArgs["executor"] = crReq.get_cookie("id");
    mArgs["status"] = crReq.get_arg("status");

    auto eReqType = DataBaseRequest::data_base_req_type::write_order;

    auto spReq = DataBaseRequest::make(eReqType, mArgs); ///@todo
    m_spDataBase->pushReq(spReq);

    return spReq->waitAndGetRes();
}

} // namespace geology
