#include "GameController.h"

GameController::GameController(QObject* parent) : QObject(parent), m_field(nullptr) {
    m_factory = new GeometricShapeFactory();
    m_generator = new SudokuGenerator(m_factory);
    m_stateManager = new StateManager();
    m_solver = new SudokuSolver();
    m_validator = new Validator();
}

GameController::~GameController() {
    if (m_field) delete m_field;
    delete m_generator;
    delete m_factory;
    delete m_stateManager;
    delete m_solver;
    delete m_validator;
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
    if (!m_field || x < 0 || y < 0) return;
    Cell* cell = m_field->getCell(x, y);
    if (cell && !cell->isInitial() && cell->getValue() != value) {
        m_stateManager->saveState(m_field);
        cell->setValue(value);
        cell->setHinted(false);
        emit fieldUpdated();
        checkGameStatus();
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
    int size = m_field->getSize();
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            int correctVal = m_field->getSolutionValue(x, y);
            m_field->getCell(x, y)->setValue(correctVal);
            m_field->getCell(x, y)->setHinted(false);
        }
    }
    emit fieldUpdated();
    emit gameFinished(true);
}
void GameController::provideHint(int x, int y) {
    if (!m_field || x < 0 || y < 0) return;
    Cell* cell = m_field->getCell(x, y);
    if (cell && !cell->isInitial()) {
        m_stateManager->saveState(m_field);
        cell->setValue(m_field->getSolutionValue(x, y));
        cell->setHinted(true);
        emit fieldUpdated();
        checkGameStatus();
    }
}

void GameController::checkGameStatus() {
    bool isFull = true;
    bool isCorrect = true;
    int size = m_field->getSize();
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            int val = m_field->getCell(x, y)->getValue();
            if (val == 0) isFull = false;
            else if (val != m_field->getSolutionValue(x, y)) isCorrect = false;
        }
    }
    if (isFull) emit gameFinished(isCorrect);
}