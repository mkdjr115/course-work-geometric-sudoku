#include "SudokuSolver.h"

SudokuSolver::SudokuSolver() {
    m_validator = new Validator();
}

SudokuSolver::~SudokuSolver() {
    delete m_validator;
}

bool SudokuSolver::solve(Field* field) {
    int x, y;
    if (!findEmptyCell(field, x, y)) return true;

    for (int num = 1; num <= field->getSize(); ++num) {
        if (m_validator->isValid(field, x, y, num)) {
            field->getCell(x, y)->setValue(num);
            if (solve(field)) return true;
            field->getCell(x, y)->setValue(0);
        }
    }
    return false;
}

bool SudokuSolver::findEmptyCell(Field* field, int& x, int& y) {
    int size = field->getSize();
    for (y = 0; y < size; ++y) {
        for (x = 0; x < size; ++x) {
            if (field->getCell(x, y)->getValue() == 0) return true;
        }
    }
    return false;
}