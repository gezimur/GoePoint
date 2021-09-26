#include <iostream>
#include <thread>

#include "AuthorizationPage.h"

int main()
{
    try
    {
        int iPort = 2345;

        httpserver::webserver WebServer = httpserver::create_webserver(iPort);

        auto spDataBase = std::make_shared<geology::GeologyDataBase>(geology::PGConnection{geology::ConnectionParams{}});

        geology::AuthorizationPage Authorization(spDataBase);
        WebServer.register_resource("/", &Authorization);
        WebServer.register_resource("/authorization", &Authorization);

        WebServer.start(true);

        return 0;
    }
    catch (std::runtime_error& rExc)
    {
        std::cout << rExc.what() << std::endl;
        return 1;
    }
}
