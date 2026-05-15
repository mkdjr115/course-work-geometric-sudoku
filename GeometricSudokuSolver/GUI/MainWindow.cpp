#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    setupUI();

    controller = new GameController(this);

    connect(generateButton, &QPushButton::clicked, this, &MainWindow::onGenerateClicked);
    connect(undoButton, &QPushButton::clicked, controller, &GameController::undo);
    connect(controller, &GameController::fieldUpdated, this, &MainWindow::onFieldUpdated);
    connect(fieldWidget, &FieldWidget::cellValueChanged, controller, &GameController::setCellValue);
}

MainWindow::~MainWindow() {
}

void MainWindow::setupUI() {
    this->setWindowTitle("Geometric Sudoku Solver");
    this->resize(800, 600);

    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);

    fieldWidget = new FieldWidget(this);
    mainLayout->addWidget(fieldWidget, 1);

    buttonLayout = new QHBoxLayout();

    generateButton = new QPushButton("Generate", this);
    solveButton = new QPushButton("Solve", this);
    hintButton = new QPushButton("Hint", this);
    undoButton = new QPushButton("Undo", this);

    buttonLayout->addWidget(generateButton);
    buttonLayout->addWidget(solveButton);
    buttonLayout->addWidget(hintButton);
    buttonLayout->addWidget(undoButton);

    mainLayout->addLayout(buttonLayout);
}

void MainWindow::onGenerateClicked() {
    controller->generateNewGame();
}

void MainWindow::onFieldUpdated() {
    fieldWidget->setField(controller->getField());
}