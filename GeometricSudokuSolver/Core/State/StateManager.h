#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <stack>
#include "FieldMemento.h"
#include "../Entities/Field.h"

class StateManager {
public:
    void saveState(Field* field);
    void undo(Field* field);
    void clear();

private:
    std::stack<FieldMemento*> m_history;
};

#endif