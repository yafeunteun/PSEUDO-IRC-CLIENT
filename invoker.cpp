#include "invoker.h"

Invoker::Invoker()
{
    m_counter = 0;
}

Invoker::~Invoker()
{
    this->clear();
}

void Invoker::clear()
{
    for ( unsigned int i = 0; i < m_history.size(); ++i )
    {
        delete m_history[i];
    }
    m_history.clear();
}


void Invoker::storeAndExecute(Command* cmd)
{
    if(m_counter >= 128)
        m_counter = 0;

    m_history[m_counter] = cmd;
    ++m_counter;
    cmd->execute();
}
