#pragma once

#include <sysinfoapi.h>

namespace geology
{

class TimeMeter
{
public:
    TimeMeter();

    int getSecFromStart();

private:
    SYSTEMTIME m_StartTime;
    SYSTEMTIME m_CurrentTime;
};

} // namespace geology

