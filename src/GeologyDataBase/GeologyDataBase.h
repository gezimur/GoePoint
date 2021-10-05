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

        int iCnt = 1;
        if (mArgs.end() != mArgs.find("cnt"))
        {
            iCnt = std::stoi(mArgs["cnt"]);
            mArgs.erase("cnt");
        }

        std::string strSortType;
        if (mArgs.end() != mArgs.find("sort_type"))
        {
            strSortType = mArgs["sort_type"];
            mArgs.erase("sort_type");
        }

        auto Res = m_upDataBaseCtrl->loadOrderGreedy(iCnt, mArgs, strSortType);

        if (Res.getMsg().empty() && Res.getTable().empty())
            spReq->setRes(DataBaseResponce{"Nothing found"});
        else
            spReq->setRes(std::move(Res));
    }

    void procLoadList(IDataBaseCtrl::enu_tables eTable, const std::shared_ptr<DataBaseRequest>& spReq)
    {
        auto mArgs = spReq->getReqArgs();

        int iCnt = 1;
        if (mArgs.end() != mArgs.find("cnt"))
        {
            iCnt = std::stoi(mArgs["cnt"]);
            mArgs.erase("cnt");
        }

        std::string strSortType;
        if (mArgs.end() != mArgs.find("sort_type"))
        {
            strSortType = mArgs["sort_type"];
            mArgs.erase("sort_type");
        }

        auto Res = m_upDataBaseCtrl->load(eTable, iCnt, mArgs, strSortType);

        if (Res.getMsg().empty() && Res.getTable().empty())
            spReq->setRes(DataBaseResponce{"Nothing found"});
        else
            spReq->setRes(std::move(Res));
    }

    void procLoadSingle(IDataBaseCtrl::enu_tables eTable, const std::shared_ptr<DataBaseRequest>& spReq)
    {
        auto mArgs = spReq->getReqArgs();

        int iId = 0;
        if (mArgs.end() != mArgs.find("id"))
        {
            iId= std::stoi(mArgs["id"]);
            spReq->setRes(m_upDataBaseCtrl->loadById(eTable, iId));
        }
        else
            spReq->setRes(DataBaseResponce{"Id not specialized"});
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
