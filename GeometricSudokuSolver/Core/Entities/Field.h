#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <map>
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
    Shape* getShapeAt(int x, int y) const;

    void setSolutionValue(int x, int y, int value);
    int getSolutionValue(int x, int y) const;

private:
    int m_size;
    std::vector<std::vector<Cell*>> m_grid;
    std::vector<std::vector<int>> m_solution;
    std::vector<Shape*> m_shapes;
    std::map<std::pair<int, int>, Shape*> m_shapeMap;
};

#endif