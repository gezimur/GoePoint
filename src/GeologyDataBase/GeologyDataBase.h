#pragma once

#include <mutex>
#include <functional>
#include <queue>
#include <algorithm>
#include <thread>

#include <DataBaseCtrl.h>

#include "DataBaseConnection.h"

namespace geology
{

class GeologyDataBase
{
    using requset_queue = std::queue<std::shared_ptr<DataBaseRequest>>;

public:
    GeologyDataBase(const PGConnection& crConnection);

    void pushReq(const std::shared_ptr<DataBaseRequest>& spRequest);

private:
    void threadProc();

    void procNextRequest();

    std::shared_ptr<DataBaseRequest> popRequest();

    template<typename t_Table>
    void procLoadList(const std::shared_ptr<DataBaseRequest>& spReq)
    {
        auto mArgs = spReq->getReqArgs();

        int iCnt = std::stoi(mArgs["cnt"]);
        mArgs.erase("cnt");

        std::string strSortType = mArgs["sort_type"];
        mArgs.erase("sort_type");

        t_Table Filter(mArgs);

        auto vRes = m_DataBaseCtrl.load<t_Table>(iCnt, Filter, strSortType);

        if (vRes.empty())
            spReq->setResMsg("Nothing found");
        else
            spReq->setResMsg("Success");

        std::vector<std::map<std::string, std::string>> vResHelp;
        std::transform(vRes.begin(), vRes.end(), std::back_inserter(vResHelp), [](const t_Table& crRes)
        {
            return crRes.getValuesMap();
        });

        spReq->setRes(vResHelp); ///@todo
    }

    template<typename t_Table>
    void procLoadSingle(const std::shared_ptr<DataBaseRequest>& spReq)
    {
        auto mArgs = spReq->getReqArgs();

        int iId = std::stoi(mArgs["id"]);

        std::string strSortType = mArgs["sort_type"];
        mArgs.erase("sort_type");

        auto Res = m_DataBaseCtrl.loadById<t_Table>(iId);

        spReq->setResMsg("Success");

        std::map<std::string, std::string> mResHelp{Res.getValuesMap()};

        spReq->setRes({mResHelp}); ///@todo
    }

    std::mutex m_Mutex;

    DataBaseCtrl m_DataBaseCtrl;

    requset_queue m_qRequest;

    std::thread m_DataBaseThread;
};

} // namespace geology
