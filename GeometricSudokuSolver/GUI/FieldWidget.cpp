#include "FieldWidget.h"

FieldWidget::FieldWidget(QWidget* parent)
    : QWidget(parent), m_field(nullptr), m_selectedX(-1), m_selectedY(-1) {
    setMinimumSize(400, 400);
    setFocusPolicy(Qt::StrongFocus);
}

void FieldWidget::setField(Field* field) {
    m_field = field;
    m_selectedX = -1;
    m_selectedY = -1;
    update();
}

Shape* FieldWidget::getShapeOfCell(int x, int y) const {
    if (!m_field) return nullptr;
    Cell* targetCell = m_field->getCell(x, y);
    for (Shape* shape : m_field->getShapes()) {
        for (Cell* cell : shape->getCells()) {
            if (cell == targetCell) return shape;
        }
    }
    return nullptr;
}

void FieldWidget::mousePressEvent(QMouseEvent* event) {
    if (!m_field) return;
    int size = m_field->getSize();
    m_selectedX = event->position().x() / (width() / (float)size);
    m_selectedY = event->position().y() / (height() / (float)size);
    update();
}

void FieldWidget::keyPressEvent(QKeyEvent* event) {
    if (!m_field || m_selectedX == -1 || m_selectedY == -1) return;
    int value = -1;
    if (event->key() >= Qt::Key_1 && event->key() <= Qt::Key_9) {
        value = event->key() - Qt::Key_0;
    }
    else if (event->key() == Qt::Key_0 || event->key() == Qt::Key_Backspace) {
        value = 0;
    }

    if (value != -1) {
        emit cellValueChanged(m_selectedX, m_selectedY, value);
    }
}

void FieldWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    if (!m_field) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int size = m_field->getSize();
    float cellW = width() / (float)size;
    float cellH = height() / (float)size;

    if (m_selectedX != -1 && m_selectedY != -1) {
        painter.fillRect(m_selectedX * cellW, m_selectedY * cellH, cellW, cellH, QColor(200, 230, 255));
    }

    painter.setPen(QPen(Qt::lightGray, 1));
    for (int i = 0; i <= size; ++i) {
        painter.drawLine(0, i * cellH, width(), i * cellH);
        painter.drawLine(i * cellW, 0, i * cellW, height());
    }

    painter.setPen(QPen(Qt::black, 3));
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            Shape* s = getShapeOfCell(x, y);
            if (x == size - 1 || getShapeOfCell(x + 1, y) != s)
                painter.drawLine((x + 1) * cellW, y * cellH, (x + 1) * cellW, (y + 1) * cellH);
            if (y == size - 1 || getShapeOfCell(x, y + 1) != s)
                painter.drawLine(x * cellW, (y + 1) * cellH, (x + 1) * cellW, (y + 1) * cellH);
            if (x == 0) painter.drawLine(0, y * cellH, 0, (y + 1) * cellH);
            if (y == 0) painter.drawLine(x * cellW, 0, (x + 1) * cellW, 0);

            int val = m_field->getCell(x, y)->getValue();
            if (val > 0) {
                painter.drawText(QRectF(x * cellW, y * cellH, cellW, cellH), Qt::AlignCenter, QString::number(val));
            }
        }
    }
}