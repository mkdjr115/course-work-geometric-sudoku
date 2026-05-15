#include "GameController.h"

GameController::GameController(QObject* parent) : QObject(parent), m_field(nullptr) {
    m_factory = new GeometricShapeFactory();
    m_generator = new SudokuGenerator(m_factory);
    m_stateManager = new StateManager();
    m_solver = new SudokuSolver();
}

GameController::~GameController() {
    if (m_field) delete m_field;
    delete m_generator;
    delete m_factory;
    delete m_stateManager;
    delete m_solver;
}

Field* GameController::getField() const {
    return m_field;
}

void GameController::generateNewGame() {
    if (m_field) delete m_field;
    m_stateManager->clear();
    m_field = m_generator->generate(9);
    emit fieldUpdated();
}

void GameController::setCellValue(int x, int y, int value) {
    if (!m_field) return;
    Cell* cell = m_field->getCell(x, y);
    if (cell && cell->getValue() != value) {
        m_stateManager->saveState(m_field);
        cell->setValue(value);
        emit fieldUpdated();
    }
}

void GameController::undo() {
    if (!m_field) return;
    m_stateManager->undo(m_field);
    emit fieldUpdated();
}

void GameController::solve() {
    if (!m_field) return;
    m_stateManager->saveState(m_field);
    m_solver->solve(m_field);
    emit fieldUpdated();
}