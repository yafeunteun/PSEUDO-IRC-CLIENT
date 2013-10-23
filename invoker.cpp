#include "invoker.h"
#include "widget.h"

Invoker* Invoker::s_instance = 0;

Invoker* Invoker::Instance()
{
    if(s_instance == 0)
        return new Invoker;

    return s_instance;
}

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

    QString frame;
    QString size;
    QString id;
    QString code;

    m_history[cmd->getId()] = cmd;         // replace 0 by cmd->getId()

    code = QString(QChar(cmd->getCode()));
    size = QString("%u").arg(cmd->getSize(), 0);      // get a string of 2 bytes containing the command ID
    id = QString("%u").arg(cmd->getId(), 0);      // get a string of 2 bytes containing the command ID

    frame = size + id + code;
    frame.replace(" ", "\n");

    Widget* w = Widget::Instance();
    w->getSocket()->write(frame.toUtf8());

}
