#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "../Core/Entities/Field.h"
#include "../Core/Generation/SudokuGenerator.h"
#include "../Core/Generation/GeometricShapeFactory.h"

class GameController : public QObject {
    Q_OBJECT
public:
    explicit GameController(QObject* parent = nullptr);
    ~GameController();

    Field* getField() const;

public slots:
    void generateNewGame();

signals:
    void fieldUpdated();

private:
    Field* m_field;
    SudokuGenerator* m_generator;
    IShapeFactory* m_factory;
};

#endif