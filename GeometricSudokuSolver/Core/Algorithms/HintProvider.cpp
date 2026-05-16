#include "HintProvider.h"
#include <vector>
#include <ctime>
#include <cstdlib>

HintProvider::HintProvider() {
    m_solver = new SudokuSolver();
    std::srand(std::time(nullptr));
}

HintProvider::~HintProvider() {
    delete m_solver;
}

bool HintProvider::provideHint(Field* field) {
    int size = field->getSize();
    Field* tempField = new Field(size);

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            tempField->getCell(x, y)->setValue(field->getCell(x, y)->getValue());
        }
    }

    for (Shape* s : field->getShapes()) {
        std::vector<Cell*> tempCells;
        for (Cell* c : s->getCells()) {
            tempCells.push_back(tempField->getCell(c->getX(), c->getY()));
        }
        Shape* tempShape = new Shape(s->getId());
        for (Cell* tc : tempCells) tempShape->addCell(tc);
        tempField->addShape(tempShape);
    }

    if (m_solver->solve(tempField)) {
        std::vector<Cell*> emptyCells;
        for (int y = 0; y < size; ++y) {
            for (int x = 0; x < size; ++x) {
                if (field->getCell(x, y)->getValue() == 0) {
                    emptyCells.push_back(field->getCell(x, y));
                }
            }
        }

        if (!emptyCells.empty()) {
            int targetIndex = std::rand() % emptyCells.size();
            Cell* target = emptyCells[targetIndex];
            int correctValue = tempField->getCell(target->getX(), target->getY())->getValue();

            target->setValue(correctValue);
            target->setHinted(true);
            delete tempField;
            return true;
        }
    }

    delete tempField;
    return false;
}