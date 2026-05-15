#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include <QWidget>
#include <QPainter>
#include "../Core/Entities/Field.h"

class FieldWidget : public QWidget {
    Q_OBJECT
public:
    explicit FieldWidget(QWidget* parent = nullptr);
    void setField(Field* field);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Field* m_field;
    Shape* getShapeOfCell(int x, int y) const;
};

#endif