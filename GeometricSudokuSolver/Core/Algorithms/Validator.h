#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "../Entities/Field.h"

class Validator {
public:
    bool isValid(Field* field, int x, int y, int value);
    bool isFieldValid(Field* field);
};

#endif