#include "GameController.h"

GameController::GameController(QObject* parent) : QObject(parent), m_field(nullptr) {
    m_factory = new GeometricShapeFactory();
    m_generator = new SudokuGenerator(m_factory);
}

GameController::~GameController() {
    if (m_field) delete m_field;
    delete m_generator;
    delete m_factory;
}

Field* GameController::getField() const {
    return m_field;
}

void GameController::generateNewGame() {
    if (m_field) {
        delete m_field;
    }
    m_field = m_generator->generate(9);
    emit fieldUpdated();
}