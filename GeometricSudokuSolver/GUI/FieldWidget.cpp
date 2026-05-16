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

int FieldWidget::getSelectedX() const {
    return m_selectedX;
}

int FieldWidget::getSelectedY() const {
    return m_selectedY;
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
    if (m_field->getCell(m_selectedX, m_selectedY)->isInitial()) return;
    int val = -1;
    if (event->key() >= Qt::Key_1 && event->key() <= Qt::Key_9) val = event->key() - Qt::Key_0;
    else if (event->key() == Qt::Key_0 || event->key() == Qt::Key_Backspace) val = 0;
    if (val != -1) emit cellValueChanged(m_selectedX, m_selectedY, val);
}

void FieldWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::white);
    if (!m_field) return;

    int size = m_field->getSize();
    float cw = width() / (float)size;
    float ch = height() / (float)size;

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            if (m_field->getCell(x, y)->isHinted())
                painter.fillRect(x * cw, y * ch, cw, ch, QColor(255, 255, 200));
        }
    }

    if (m_selectedX != -1 && m_selectedY != -1)
        painter.fillRect(m_selectedX * cw, m_selectedY * ch, cw, ch, QColor(200, 230, 255));

    painter.setPen(QPen(Qt::lightGray, 1));
    for (int i = 0; i <= size; ++i) {
        painter.drawLine(0, i * ch, width(), i * ch);
        painter.drawLine(i * cw, 0, i * cw, height());
    }

    painter.setPen(QPen(Qt::black, 3));
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            Shape* s = m_field->getShapeAt(x, y);
            if (x == size - 1 || m_field->getShapeAt(x + 1, y) != s)
                painter.drawLine((x + 1) * cw, y * ch, (x + 1) * cw, (y + 1) * ch);
            if (y == size - 1 || m_field->getShapeAt(x, y + 1) != s)
                painter.drawLine(x * cw, (y + 1) * ch, (x + 1) * cw, (y + 1) * ch);
            if (x == 0) painter.drawLine(0, y * ch, 0, (y + 1) * ch);
            if (y == 0) painter.drawLine(x * cw, 0, (x + 1) * cw, 0);

            int val = m_field->getCell(x, y)->getValue();
            if (val > 0) {
                painter.setPen(Qt::black);
                QFont f = painter.font();
                f.setBold(m_field->getCell(x, y)->isInitial());
                painter.setFont(f);
                painter.drawText(QRectF(x * cw, y * ch, cw, ch), Qt::AlignCenter, QString::number(val));
                painter.setPen(QPen(Qt::black, 3));
            }
        }
    }
}