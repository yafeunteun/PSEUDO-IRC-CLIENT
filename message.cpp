#include "message.h"
#include "widget.h"
#include <iostream>


Message::Message(QString &args)
{
    m_args = args;
}


/*************************
 *  ajoin                *
 ************************/

ajoin::ajoin(QString& args) : Message(args)
{
}


void ajoin::execute()
{
    Widget *w = Widget::Instance();
    w->getOutputArea()->append("[JOIN] " + m_args);
}
