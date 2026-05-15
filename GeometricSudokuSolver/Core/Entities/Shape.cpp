#include "Shape.h"

Shape::Shape(int id) : m_id(id) {
}

int Shape::getId() const {
    return m_id;
}

void Shape::addCell(Cell* cell) {
    m_cells.push_back(cell);
}

std::vector<Cell*> Shape::getCells() const {
    return m_cells;
}