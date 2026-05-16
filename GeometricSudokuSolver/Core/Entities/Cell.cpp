#include "Cell.h"

Cell::Cell(int x, int y) : m_x(x), m_y(y), m_value(0), m_isInitial(false), m_isHinted(false) {
}

int Cell::getX() const {
    return m_x;
}

int Cell::getY() const {
    return m_y;
}

int Cell::getValue() const {
    return m_value;
}

void Cell::setValue(int value) {
    m_value = value;
}

bool Cell::isInitial() const {
    return m_isInitial;
}

void Cell::setInitial(bool initial) {
    m_isInitial = initial;
}

bool Cell::isHinted() const {
    return m_isHinted;
}

void Cell::setHinted(bool hinted) {
    m_isHinted = hinted;
}