#ifndef INVOKER_H
#define INVOKER_H

#include <QtGlobal>
#include <vector>
#include "command.h"

class Invoker
{
public:
    static Invoker* Instance();
    ~Invoker();
    void storeAndExecute(Command* cmd);
    Command* getCommand(quint16 commandId);

private:
    Invoker();
    static Invoker* s_instance;
    std::vector<Command*> m_history;
    void clear(void);
};

#endif // INVOKER_H
