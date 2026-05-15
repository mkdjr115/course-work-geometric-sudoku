#include "GeometricShapeFactory.h"

Shape* GeometricShapeFactory::createShape(int id, const std::vector<Cell*>& cells) {
    Shape* newShape = new Shape(id);
    for (Cell* cell : cells) {
        newShape->addCell(cell);
    }
    return newShape;
}