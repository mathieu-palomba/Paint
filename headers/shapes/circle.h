#ifndef CIRCLE_H
#define CIRCLE_H

#include <QPoint>
#include "shapes/shape.h"

class Circle : public Shape
{
    Q_OBJECT

public:
    Circle(QPen& pen, QBrush& brush);
    ~Circle();

    void draw(QPixmap& pixmap);

private:
    QPoint _startPoint, _endPoint;

public slots:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // CIRCLE_H
