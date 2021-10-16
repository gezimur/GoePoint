#pragma once

#include <mutex>
#include <functional>
#include <queue>
#include <algorithm>
#include <thread>

#include <IDataBaseCtrl.h>

#include "DataBaseRequest.h"

namespace geology
{

class GeologyDataBase
{
    using requset_queue = std::queue<std::shared_ptr<DataBaseRequest>>;

public:
    explicit GeologyDataBase(const ConnectionParams& crParams);

    void pushReq(const std::shared_ptr<DataBaseRequest>& spRequest);

private:
    void threadProc();

    void procNextRequest();

    std::shared_ptr<DataBaseRequest> popRequest();

    void procLoadOrderGreedy(const std::shared_ptr<DataBaseRequest>& spReq)
    {
        auto mArgs = spReq->getReqArgs();

        auto Res = m_upDataBaseCtrl->loadOrderGreedy(spReq->getCnt(), mArgs, spReq->getSortType());

        if (Res.getMsg().empty() && Res.getTable().empty())
            spReq->setRes(DataBaseResponce{"Nothing found"});
        else
            spReq->setRes(std::move(Res));
    }

    void procLoadList(IDataBaseCtrl::enu_tables eTable, const std::shared_ptr<DataBaseRequest>& spReq)
    {
        auto mArgs = spReq->getReqArgs();

        auto Res = m_upDataBaseCtrl->load(eTable, spReq->getCnt(), mArgs, spReq->getSortType());

        if (Res.getMsg().empty() && Res.getTable().empty())
            spReq->setRes(DataBaseResponce{"Nothing found"});
        else
            spReq->setRes(std::move(Res));
    }

    void procWrite(IDataBaseCtrl::enu_tables eTable, const std::shared_ptr<DataBaseRequest>& spReq)
    {
        auto mArgs = spReq->getReqArgs();

        auto Res = m_upDataBaseCtrl->write(eTable, mArgs);

        if (Res.getMsg().empty())
            Res.setMsg("Success");

        spReq->setRes(Res);
    }


    std::mutex m_Mutex;

    std::unique_ptr<IDataBaseCtrl> m_upDataBaseCtrl;

    requset_queue m_qRequest;

    std::thread m_DataBaseThread;
};

} // namespace geology
