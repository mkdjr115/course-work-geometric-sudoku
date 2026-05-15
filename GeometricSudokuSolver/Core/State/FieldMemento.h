#ifndef FIELDMEMENTO_H
#define FIELDMEMENTO_H

#include <vector>

class FieldMemento {
public:
    FieldMemento(const std::vector<int>& values);
    std::vector<int> getValues() const;

private:
    std::vector<int> m_values;
};

#endif