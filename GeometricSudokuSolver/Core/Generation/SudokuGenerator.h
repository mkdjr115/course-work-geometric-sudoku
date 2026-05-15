#ifndef SUDOKUGENERATOR_H
#define SUDOKUGENERATOR_H

#include "../Entities/Field.h"
#include "IShapeFactory.h"

class SudokuGenerator {
public:
    SudokuGenerator(IShapeFactory* factory);
    Field* generate(int size);

private:
    IShapeFactory* m_factory;
};

#endif