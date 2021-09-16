#pragma once

#include <WinSock2.h>

namespace geology
{

class GeologyServer
{
public:
    GeologyServer(int iPort);

    int start();
    void stop();

    int getPort() const noexcept;
    void setPort(int iPort) noexcept;

private:
    int m_iPort;
    WSADATA m_WsaData;

};

} // namespace geology
