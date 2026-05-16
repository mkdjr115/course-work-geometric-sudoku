#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "../Core/Entities/Field.h"
#include "../Core/Generation/SudokuGenerator.h"
#include "../Core/Generation/GeometricShapeFactory.h"
#include "../Core/State/StateManager.h"
#include "../Core/Algorithms/SudokuSolver.h"
#include "../Core/Algorithms/HintProvider.h"
#include "../Core/Algorithms/Validator.h"

class GameController : public QObject {
    Q_OBJECT
public:
    explicit GameController(QObject* parent = nullptr);
    ~GameController();

    Field* getField() const;

public slots:
    void generateNewGame();
    void setCellValue(int x, int y, int value);
    void undo();
    void solve();
    void provideHint(int x, int y);

signals:
    void fieldUpdated();
    void gameFinished(bool won);

private:
    Field* m_field;
    SudokuGenerator* m_generator;
    IShapeFactory* m_factory;
    StateManager* m_stateManager;
    SudokuSolver* m_solver;
    HintProvider* m_hintProvider;
    Validator* m_validator;

    void checkGameStatus();
};

#endif