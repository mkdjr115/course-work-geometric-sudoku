#include "StateManager.h"

void StateManager::saveState(Field* field) {
    std::vector<int> values;
    int size = field->getSize();
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            values.push_back(field->getCell(x, y)->getValue());
        }
    }
    m_history.push(new FieldMemento(values));
}

void StateManager::undo(Field* field) {
    if (m_history.empty()) return;

    FieldMemento* memento = m_history.top();
    m_history.pop();

    std::vector<int> values = memento->getValues();
    int size = field->getSize();
    int index = 0;
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            field->getCell(x, y)->setValue(values[index++]);
        }
    }
    delete memento;
}

void StateManager::clear() {
    while (!m_history.empty()) {
        delete m_history.top();
        m_history.pop();
    }
}