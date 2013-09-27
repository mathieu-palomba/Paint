#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QPoint>
#include "shape.h"

class Rectangle : public Shape
{
    Q_OBJECT

public:
    Rectangle(QPen& pen, QBrush& brush);
    ~Rectangle();

    void draw(QPixmap& pixmap);

private:
    QPoint _startPoint, _endPoint;

public slots:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // RECTANGLE_H
