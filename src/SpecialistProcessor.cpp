#include "SpecialistProcessor.h"

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
        return proc_html_responce(m_spPages->getOrderListPage(), 200); ///@todo manager page

    if (std::string::npos == strPath.find("/order"))
        return proc_exit(); ///@todo exception page

    return proc_html_responce(m_spPages->getOrderPage(), 200); ///@todo manager page
}

SpecialistProcessor::responce_type SpecialistProcessor::processPOST(const httpserver::http_request& crReq)
{
    auto vPath = crReq.get_path_pieces();

    if ("order" != vPath[0])
        return proc_msg_responce("Unknow request", 200);

    if (2 == vPath.size())
        return procGetOrder(vPath[1]);
//    if (3 == vPath.size())
//        return procSaveOrder(vPath[1]);

    return proc_msg_responce("Invalid request", 200);
}

SpecialistProcessor::responce_type SpecialistProcessor::procGetOrder(const std::string& strOrderId)
{
    auto spReq = DataBaseRequest::make(DataBaseRequest::data_base_req_type::get_order, {{"id", strOrderId}});
    m_spDataBase->pushReq(spReq);

    auto Res = spReq->waitAndGetRes();

    return proc_json_responce(Res, 200);
}

//SpecialistProcessor::responce_type SpecialistProcessor::procSaveOrder(const std::string& strOrderId)
//{
//    auto spReq = DataBaseRequest::make(DataBaseRequest::data_base_req_type::save_order, {{"id", strOrderId}}); ///@todo
//    m_spDataBase->pushReq(spReq);

//    auto Res = spReq->waitAndGetRes();

//    return proc_json_responce(Res, 200);
//}

} // namespace geology
