#include <iostream>
#include <thread>

#include <ws2tcpip.h>

#include "GeologyServer.h"
#include "Common/TimeMeter.h"

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
