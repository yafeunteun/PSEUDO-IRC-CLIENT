#include "command.h"
#include "widget.h"
#include "invoker.h"

quint16 Command::s_counter = 0;


Command::Command(QString &args)
{
    m_args = args;
    m_size = args.size()+3;
    m_id = s_counter;
    if(s_counter >= 128)
        s_counter = 0;
    else ++s_counter;
}

void Command::execute()
{
     Invoker* i = Invoker::Instance();
    i->storeAndExecute(this);
}

/*************************
 *  PVMSGCommand         *
 ************************/

PVMSGCommand::PVMSGCommand(QString& args) : Command(args)
{
    m_code = CMD::C_PVMSG;
}

void PVMSGCommand::throwError(quint8 code)
{
    if(code == 2)
    {
        Widget* w = Widget::Instance();
        w->displayError(QString("hhh"));
    }
}
