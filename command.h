#ifndef COMMAND_H
#define COMMAND_H

#include <QtGlobal>
#include <QString>

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
    // +4 : 2 bytes for command Id, 1 byte for command number, 1 byte for '\n' end char
    Command(QString& args);
    virtual ~Command() {}
    virtual void execute(void);
    virtual void throwError(quint8) = 0;
    virtual quint16 getId(void) const{return m_id;}
    virtual quint8 getCode(void) const{return m_code;}
    virtual quint16 getSize(void) const{return m_size;}

protected:
    static quint16 s_counter;
    quint8 m_code;
    quint16 m_size;
    quint16 m_id;
    QString m_args;
};

class PVMSGCommand : public Command
{
public:
    PVMSGCommand(QString& args);
    virtual void throwError(quint8);
private:


};

#endif // COMMAND_H
