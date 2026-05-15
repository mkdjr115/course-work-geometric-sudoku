#include "FieldMemento.h"

FieldMemento::FieldMemento(const std::vector<int>& values) : m_values(values) {
}

std::vector<int> FieldMemento::getValues() const {
    return m_values;
}