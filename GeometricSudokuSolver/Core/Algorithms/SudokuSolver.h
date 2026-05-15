#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include "../Entities/Field.h"
#include "Validator.h"

class SudokuSolver {
public:
    SudokuSolver();
    ~SudokuSolver();
    bool solve(Field* field);

private:
    Validator* m_validator;
    bool findEmptyCell(Field* field, int& x, int& y);
};

#endif