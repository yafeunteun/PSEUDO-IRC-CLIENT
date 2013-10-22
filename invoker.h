#ifndef INVOKER_H
#define INVOKER_H

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
    unsigned char m_counter;

    void clear(void);
};

#endif // INVOKER_H
