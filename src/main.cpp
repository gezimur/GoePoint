#include <iostream>
#include <thread>

#include <ws2tcpip.h>

#include "GeologyServer.h"
#include "Common/TimeMeter.h"

void collect_garbage(std::list<std::shared_ptr<geology::ClientProcessor>>& lClientProcessor)
{
    std::cout << "collectGarbage(), size: " << lClientProcessor.size() << std::endl;
    for (auto it = lClientProcessor.begin(); it != lClientProcessor.end(); )
    {
        std::cout << "collectGarbage() " << std::endl;

        if(!(*it)->isInitialized())
        {
            std::cout << "erase client, size before: " << lClientProcessor.size();
            lClientProcessor.erase(it);
            std::cout << " size after: " << lClientProcessor.size() << std::endl;
        }
        else
        {
            std::cout << "collectGarbage() go next " << std::endl;
            ++it;
        }

        std::cout << "collectGarbage() after" << std::endl;
    }
}

int main()
{
    try
    {
        int iPort = 2345;

        geology::GeologyServer Server(iPort);

        Server.start();

//        std::list<std::shared_ptr<geology::ClientProcessor>> lClientProcessor;
//        lClientProcessor.push_back(std::make_shared<geology::ClientProcessor>(INVALID_SOCKET, nullptr));

//        Sleep(200);

//        collect_garbage(lClientProcessor);

//        geology::ClientProcessor(INVALID_SOCKET, nullptr);

        return 0;
    }
    catch (std::runtime_error& rExc)
    {
        std::cout << rExc.what() << std::endl;
        return 1;
    }
}
