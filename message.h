#ifndef MESSAGE_H
#define MESSAGE_H

#include "widget.h"


namespace FROMSERVER {

enum{
        C_APUBMSG = 128,
        C_APRIVMSG,
        C_AOP,
        C_ATOPIC,
        C_ANICK,
        C_ALEAVE,
        C_AKICK,
        C_ABAN,
        C_RWALL,
        C_AJOIN
    };

}


class Message
{
public:
    Message(QString& args);
    virtual ~Message() {}
    virtual void execute(void) = 0;

protected:
    QString m_args;
};


class ajoin: public Message
{

public:
    ajoin(QString& args);
    virtual void execute(void);

};

#endif // MESSAGE_H
