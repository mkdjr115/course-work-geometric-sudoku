#ifndef HINTPROVIDER_H
#define HINTPROVIDER_H

#include "../Entities/Field.h"
#include "SudokuSolver.h"

class HintProvider {
public:
    HintProvider();
    ~HintProvider();
    bool provideHint(Field* field);

private:
    SudokuSolver* m_solver;
};

#endif