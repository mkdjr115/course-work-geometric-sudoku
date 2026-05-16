#include "Field.h"

Field::Field(int size) : m_size(size) {
    m_grid.resize(m_size);
    m_solution.resize(m_size, std::vector<int>(m_size, 0));
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
    for (Cell* cell : shape->getCells()) {
        m_shapeMap[{cell->getX(), cell->getY()}] = shape;
    }
}

std::vector<Shape*> Field::getShapes() const {
    return m_shapes;
}

Shape* Field::getShapeAt(int x, int y) const {
    auto it = m_shapeMap.find({ x, y });
    if (it != m_shapeMap.end()) {
        return it->second;
    }
    return nullptr;
}

void Field::setSolutionValue(int x, int y, int value) {
    if (x >= 0 && x < m_size && y >= 0 && y < m_size) {
        m_solution[y][x] = value;
    }
}

int Field::getSolutionValue(int x, int y) const {
    if (x >= 0 && x < m_size && y >= 0 && y < m_size) {
        return m_solution[y][x];
    }
    return 0;
}