#ifndef ISHAPEFACTORY_H
#define ISHAPEFACTORY_H

#include "../Entities/Shape.h"
#include "../Entities/Field.h"

class IShapeFactory {
public:
    virtual ~IShapeFactory() = default;
    virtual Shape* createShape(int id, const std::vector<Cell*>& cells) = 0;
};

#endif