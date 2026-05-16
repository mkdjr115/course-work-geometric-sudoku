#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include "FieldWidget.h"
#include "../App/GameController.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onGenerateClicked();
    void onHintClicked();
    void onFieldUpdated();
    void onGameFinished(bool won);

private:
    QWidget* centralWidget;
    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonLayout;
    QPushButton* generateButton;
    QPushButton* solveButton;
    QPushButton* hintButton;
    QPushButton* undoButton;

    FieldWidget* fieldWidget;
    GameController* controller;

    void setupUI();
};

#endif