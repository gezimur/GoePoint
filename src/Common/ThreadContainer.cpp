#include "ThreadContainer.h"

namespace geology
{

ThreadContainer::ThreadContainer(std::function<void()> fThreadFunc)
    : m_Thread(fThreadFunc)
{

}

ThreadContainer::~ThreadContainer()
{
    m_Thread.join();
}

} // namespace geology
