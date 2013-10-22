#ifndef COMMAND_H
#define COMMAND_H

#include <QtGlobal>

namespace CMD {
    enum{
            C_PVMSG = 1,
            C_MSG,
            C_GWHO,
            C_CWHO,
            C_LIST,
            C_TOPIC,
            C_KICK,
            C_BAN,
            C_OP,
            C_DEOP = 20,
            C_JOIN,
            C_NICK,
            C_LEAVE,
            C_UNBAN,
            C_BANLIST
        };

}


class Command
{
public:
    Command() {m_id = s_counter; if(s_counter >= 128) s_counter = 0; else ++s_counter;}
    virtual ~Command();
    virtual void execute(void) = 0;
    virtual void throwError(quint8);
    quint16 getId(void) const{return m_id;}

private:
    static quint16 s_counter;
    quint16 m_size;
    quint16 m_id;
};
#endif // COMMAND_H
