#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include "../Core/Entities/Field.h"

class FieldWidget : public QWidget {
    Q_OBJECT
public:
    explicit FieldWidget(QWidget* parent = nullptr);
    void setField(Field* field);

    int getSelectedX() const;
    int getSelectedY() const;

signals:
    void cellValueChanged(int x, int y, int value);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    Field* m_field;
    int m_selectedX;
    int m_selectedY;
};

#endif