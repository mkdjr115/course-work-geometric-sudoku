#include "GeometricSudokuSolver.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GeometricSudokuSolver window;
    window.show();
    return app.exec();
}
