#include "Field.h"

Field::Field(int size) : m_size(size) {
    m_grid.resize(m_size);
    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            m_grid[i].push_back(new Cell(j, i));
        }
    }
}

Field::~Field() {
    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            delete m_grid[i][j];
        }
    }
    for (Shape* shape : m_shapes) {
        delete shape;
    }
}

int Field::getSize() const {
    return m_size;
}

Cell* Field::getCell(int x, int y) const {
    if (x >= 0 && x < m_size && y >= 0 && y < m_size) {
        return m_grid[y][x];
    }
    return nullptr;
}

void Field::addShape(Shape* shape) {
    m_shapes.push_back(shape);
}

std::vector<Shape*> Field::getShapes() const {
    return m_shapes;
}