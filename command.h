#ifndef COMMAND_H
#define COMMAND_H

#include <QtGlobal>
#include <QString>


namespace ERROR {
    enum{
        eBadArg = 250,
        eNickCollision,
        eNotAuthorised,
        eMissingArg,
        eNotExist,
        error
    };

}


namespace TOSERVER {


    enum{
            C_PRIVMSG = 1,
            C_PUBMSG,
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
    Command(QString& args);
    virtual ~Command() {}
    virtual void execute(void);
    virtual void throwError(quint8) {}
    virtual quint16 getId(void) const{return m_id;}
    virtual quint8 getCode(void) const{return m_code;}
    virtual quint16 getSize(void) const{return m_size;}
    virtual QString getArgs(void) const{return m_args;}

protected:
    static quint16 s_counter;
    quint8 m_code;
    quint16 m_size;
    quint16 m_id;
    QString m_args;
    // QRegExp pattern;
};



    class privmsg : public Command
    {
    public:
        privmsg(QString& args);
        virtual void throwError(quint8);

    };

    class pubmsg : public Command
    {
    public:
        pubmsg(QString& args);
        virtual void throwError(quint8);
    };


    class join : public Command
    {
    public:
        join(QString& args);
        virtual void throwError(quint8);
    };





#endif // COMMAND_H
