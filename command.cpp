#include "command.h"
#include "widget.h"
#include "invoker.h"
#include <QRegExp>

#include <iostream>

using namespace TOSERVER;

quint16 Command::s_counter = 0;


Command::Command(QString &args)
{
    m_args = args;
    m_size = args.size()+3; // 2 for m_id; 1 for m_code
    m_id = s_counter;
    if(s_counter >= 128)
        s_counter = 0;
    else ++s_counter;

    std::cout<<"size :"<<m_size<<std::endl;
    //std::cout<<"id: "<<m_id<<std::endl;
}

void Command::execute()
{
    Invoker* i = Invoker::Instance();
    i->storeAndExecute(this);
}



/*************************
 *  PVMSGCommand         *
 ************************/

privmsg::privmsg(QString& args) : Command(args)
{
    m_code = C_PRIVMSG;
}

void privmsg::throwError(quint8 code)
{
    if(code == 2)
    {
        Widget* w = Widget::Instance();
        w->displayError(QString("Unknown client !"));
    }
}

/*************************
 *  MSGCommand           *
 ************************/
pubmsg::pubmsg(QString& args) : Command(args)
{
    m_code = C_PUBMSG;
    Widget *w = Widget::Instance();
    w->getOutputArea()->append(m_args + "\n");
}


void pubmsg::throwError(quint8 code)
{

}

/*************************
 *  JOINCommand           *
 ************************/
join::join(QString& args) : Command(args)
{
    m_code = C_JOIN;
}


void join::throwError(quint8 code)
{
    Widget* w = Widget::Instance();

    if(code == 0)
    {
        QStringList n(this->getArgs());
        QTreeWidgetItem *item = new QTreeWidgetItem(n);

        w->getTree()->addTopLevelItem(item);

        return;
    }

    switch(code)
    {
    case ERROR::eNotAuthorised: w->displayError("You've been banned from this channel !");break;
    case ERROR::eMissingArg: w->displayError("You must give a channel name !");break;
    default : w->displayError("An unknown error has occured !");break;
    }


}

