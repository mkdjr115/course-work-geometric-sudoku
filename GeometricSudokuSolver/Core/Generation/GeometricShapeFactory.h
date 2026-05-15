#ifndef GEOMETRICSHAPEFACTORY_H
#define GEOMETRICSHAPEFACTORY_H

#include "IShapeFactory.h"

class GeometricShapeFactory : public IShapeFactory {
public:
    Shape* createShape(int id, const std::vector<Cell*>& cells) override;
};

#endif