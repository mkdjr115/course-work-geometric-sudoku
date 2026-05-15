#include "FieldWidget.h"

FieldWidget::FieldWidget(QWidget* parent) : QWidget(parent), m_field(nullptr) {
    setMinimumSize(400, 400);
}

void FieldWidget::setField(Field* field) {
    m_field = field;
    update();
}

Shape* FieldWidget::getShapeOfCell(int x, int y) const {
    if (!m_field) return nullptr;
    Cell* targetCell = m_field->getCell(x, y);
    for (Shape* shape : m_field->getShapes()) {
        for (Cell* cell : shape->getCells()) {
            if (cell == targetCell) {
                return shape;
            }
        }
    }
    return nullptr;
}

void FieldWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    if (!m_field) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int size = m_field->getSize();
    float cellWidth = width() / static_cast<float>(size);
    float cellHeight = height() / static_cast<float>(size);

    QPen gridPen(Qt::lightGray, 1);
    painter.setPen(gridPen);
    for (int i = 0; i <= size; ++i) {
        painter.drawLine(0, i * cellHeight, width(), i * cellHeight);
        painter.drawLine(i * cellWidth, 0, i * cellWidth, height());
    }

    QPen shapePen(Qt::black, 3);
    painter.setPen(shapePen);
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            Shape* currentShape = getShapeOfCell(x, y);

            if (x == size - 1 || getShapeOfCell(x + 1, y) != currentShape) {
                painter.drawLine((x + 1) * cellWidth, y * cellHeight, (x + 1) * cellWidth, (y + 1) * cellHeight);
            }
            if (y == size - 1 || getShapeOfCell(x, y + 1) != currentShape) {
                painter.drawLine(x * cellWidth, (y + 1) * cellHeight, (x + 1) * cellWidth, (y + 1) * cellHeight);
            }
            if (x == 0) {
                painter.drawLine(0, y * cellHeight, 0, (y + 1) * cellHeight);
            }
            if (y == 0) {
                painter.drawLine(x * cellWidth, 0, (x + 1) * cellWidth, 0);
            }
        }
    }
}