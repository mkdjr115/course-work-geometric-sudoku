#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "Cell.h"

class Shape {
public:
    Shape(int id);
    int getId() const;
    void addCell(Cell* cell);
    std::vector<Cell*> getCells() const;

private:
    int m_id;
    std::vector<Cell*> m_cells;
};

#endif