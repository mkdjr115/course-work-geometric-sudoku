#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include "Cell.h"
#include "Shape.h"

class Field {
public:
    Field(int size);
    ~Field();

    int getSize() const;
    Cell* getCell(int x, int y) const;
    void addShape(Shape* shape);
    std::vector<Shape*> getShapes() const;

private:
    int m_size;
    std::vector<std::vector<Cell*>> m_grid;
    std::vector<Shape*> m_shapes;
};

#endif