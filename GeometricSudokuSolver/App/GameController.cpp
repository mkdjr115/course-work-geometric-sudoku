#include "GameController.h"

GameController::GameController(QObject* parent) : QObject(parent), m_field(nullptr) {
}

GameController::~GameController() {
    if (m_field) {
        delete m_field;
    }
}

Field* GameController::getField() const {
    return m_field;
}

void GameController::generateNewGame() {
    if (m_field) {
        delete m_field;
    }

    m_field = new Field(9);
    int shapeId = 1;

    for (int r = 0; r < 9; r += 3) {
        for (int c = 0; c < 9; c += 3) {
            Shape* shape = new Shape(shapeId++);
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    shape->addCell(m_field->getCell(c + j, r + i));
                }
            }
            m_field->addShape(shape);
        }
    }

    emit fieldUpdated();
}