#pragma once

#include <thread>
#include <functional>

namespace geology
{

class ThreadContainer
{
public:
    explicit ThreadContainer(std::function<void()> fThreadFunc);
    ~ThreadContainer();

private:
    std::thread m_Thread;
};

} // namespace geology

