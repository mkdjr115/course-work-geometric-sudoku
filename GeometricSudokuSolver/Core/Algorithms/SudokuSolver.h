#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include "../Entities/Field.h"
#include "Validator.h"
#include <vector>

class SudokuSolver {
public:
    SudokuSolver();
    ~SudokuSolver();
    bool solve(Field* field);

private:
    Validator* m_validator;
    bool findBestEmptyCell(Field* field, int& x, int& y);
    std::vector<int> getValidCandidates(Field* field, int x, int y);
};

#endif