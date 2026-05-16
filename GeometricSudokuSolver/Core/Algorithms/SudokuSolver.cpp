#include "SudokuSolver.h"
#include <algorithm>
#include <random>
#include <vector>

SudokuSolver::SudokuSolver() {
    m_validator = new Validator();
}

SudokuSolver::~SudokuSolver() {
    delete m_validator;
}

bool SudokuSolver::solve(Field* field) {
    int x = -1, y = -1;
    if (!findBestEmptyCell(field, x, y)) return true;

    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    static std::random_device rd;
    static std::mt19937 g(rd());
    std::shuffle(numbers.begin(), numbers.end(), g);

    for (int num : numbers) {
        if (m_validator->isValid(field, x, y, num)) {
            field->getCell(x, y)->setValue(num);
            if (solve(field)) return true;
            field->getCell(x, y)->setValue(0);
        }
    }
    return false;
}

bool SudokuSolver::findBestEmptyCell(Field* field, int& x, int& y) {
    int size = field->getSize();
    int minOptions = 10;
    bool found = false;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (field->getCell(j, i)->getValue() == 0) {
                int options = 0;
                for (int n = 1; n <= size; ++n) {
                    if (m_validator->isValid(field, j, i, n)) options++;
                }

                if (options == 0) return false;

                if (options < minOptions) {
                    minOptions = options;
                    x = j;
                    y = i;
                    found = true;
                }
                if (minOptions == 1) return true;
            }
        }
    }
    return found;
}