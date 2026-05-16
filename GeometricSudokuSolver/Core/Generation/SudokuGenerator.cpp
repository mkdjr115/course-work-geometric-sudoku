#include "SudokuGenerator.h"
#include <ctime>
#include <cstdlib>
#include <vector>
#include "../Algorithms/SudokuSolver.h"

SudokuGenerator::SudokuGenerator(IShapeFactory* factory) : m_factory(factory) {
    std::srand(std::time(nullptr));
}

Field* SudokuGenerator::generate(int size) {
    bool generated = false;
    Field* field = nullptr;

    while (!generated) {
        if (field) delete field;
        field = new Field(size);

    int patterns[3][9][9] = {
        {
            {1,1,1,1,1,2,2,2,2},
            {3,1,1,1,1,4,2,2,2},
            {3,3,4,4,4,4,5,2,2},
            {3,3,4,4,4,4,5,5,5},
            {3,3,5,5,5,5,5,8,8},
            {3,3,7,7,7,8,8,8,8},
            {6,7,7,7,7,8,8,8,9},
            {6,7,7,9,9,9,9,9,9},
            {6,6,6,6,6,6,6,9,9}
        },
        {
            {1,1,1,3,4,4,4,4,4},
            {1,2,2,3,3,4,4,4,6},
            {1,2,2,3,5,4,6,6,6},
            {1,2,2,3,5,5,6,6,6},
            {1,2,3,3,5,8,6,6,8},
            {1,2,3,3,5,8,8,8,8},
            {1,2,5,5,5,8,9,9,9},
            {7,7,5,7,7,8,9,9,9},
            {7,7,7,7,7,8,9,9,9}
        },
        {
            {1,2,2,2,2,3,3,4,4},
            {1,1,2,2,3,3,4,4,4},
            {1,1,2,2,3,3,4,8,8},
            {1,5,5,2,3,3,4,8,8},
            {1,5,6,6,3,7,4,8,8},
            {1,5,6,6,6,7,4,8,8},
            {1,5,6,7,7,7,9,9,8},
            {5,5,6,7,7,7,9,9,9},
            {5,5,6,6,7,9,9,9,9}
        }
    };

    int selected = std::rand() % 3;
    for (int id = 1; id <= 9; ++id) {
        std::vector<Cell*> shapeCells;
        for (int y = 0; y < 9; ++y) {
            for (int x = 0; x < 9; ++x) {
                if (patterns[selected][y][x] == id) shapeCells.push_back(field->getCell(x, y));
            }
        }
        field->addShape(m_factory->createShape(id, shapeCells));
    }

    SudokuSolver solver;
    if (solver.solve(field)) {
        bool isFull = true;
        for (int y = 0; y < 9; ++y) {
            for (int x = 0; x < 9; ++x) {
                if (field->getCell(x, y)->getValue() == 0) isFull = false;
            }
        }

        if (isFull) {
            for (int y = 0; y < 9; ++y) {
                for (int x = 0; x < 9; ++x) {
                    int val = field->getCell(x, y)->getValue();
                    field->setSolutionValue(x, y, val);
                    if (std::rand() % 100 >= 30) {
                        field->getCell(x, y)->setValue(0);
                        field->getCell(x, y)->setInitial(false);
                    }
                    else {
                        field->getCell(x, y)->setInitial(true);
                    }
                }
            }
            generated = true;
        }
    }
    }
    return field;
}