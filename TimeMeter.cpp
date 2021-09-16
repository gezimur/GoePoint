#include "TimeMeter.h"

namespace geology
{

int calc_time(const SYSTEMTIME& crTime)
{
    return static_cast<int>(crTime.wHour) * 3600 + static_cast<int>(crTime.wMinute) * 60 + static_cast<int>(crTime.wSecond);
}

TimeMeter::TimeMeter()
{
    GetSystemTime(&m_StartTime);
}

int TimeMeter::getSecFromStart()
{
    GetSystemTime(&m_CurrentTime);

    int iStartTime_sec = calc_time(m_StartTime);
    int iCurrentTime_sec = calc_time(m_CurrentTime);
    return iCurrentTime_sec - iStartTime_sec;
}

} // namespace geology
