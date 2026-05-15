#include "SudokuGenerator.h"

SudokuGenerator::SudokuGenerator(IShapeFactory* factory) : m_factory(factory) {
}

Field* SudokuGenerator::generate(int size) {
    Field* field = new Field(size);
    int shapeId = 1;

    if (size == 9) {
        for (int r = 0; r < 9; r += 3) {
            for (int c = 0; c < 9; c += 3) {
                std::vector<Cell*> shapeCells;
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        shapeCells.push_back(field->getCell(c + j, r + i));
                    }
                }
                field->addShape(m_factory->createShape(shapeId++, shapeCells));
            }
        }
    }

    return field;
}