#include "invoker.h"

Invoker::Invoker()
{
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
    m_history[0] = cmd;         // replace 0 by cmd->getId()
    cmd->execute();
}
