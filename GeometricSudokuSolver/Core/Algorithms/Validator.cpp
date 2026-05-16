#include "Validator.h"

bool Validator::isValid(Field* field, int x, int y, int value) {
    if (value == 0) return true;
    int size = field->getSize();

    for (int i = 0; i < size; ++i) {
        if (i != x && field->getCell(i, y)->getValue() == value) return false;
        if (i != y && field->getCell(x, i)->getValue() == value) return false;
    }

    Shape* shape = field->getShapeAt(x, y);
    if (shape) {
        for (Cell* cell : shape->getCells()) {
            if (cell->getX() == x && cell->getY() == y) continue;
            if (cell->getValue() == value) return false;
        }
    }

    return true;
}

bool Validator::isFieldValid(Field* field) {
    int size = field->getSize();
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            int val = field->getCell(x, y)->getValue();
            if (val != 0) {
                field->getCell(x, y)->setValue(0);
                bool valid = isValid(field, x, y, val);
                field->getCell(x, y)->setValue(val);
                if (!valid) return false;
            }
        }
    }
    return true;
}