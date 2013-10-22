#ifndef INVOKER_H
#define INVOKER_H

#include <QtGlobal>
#include <vector>
#include "command.h"

class Invoker
{
public:
    Invoker();
    ~Invoker();
    void storeAndExecute(Command* cmd);

private:
    std::vector<Command*> m_history;
    void clear(void);
};

#endif // INVOKER_H
