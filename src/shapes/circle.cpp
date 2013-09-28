#include "shapes/circle.h"

Circle::Circle(QPen& pen, QBrush& brush) :
    Shape(pen, brush)
{
}

Circle::~Circle()
{
}

void Circle::draw(QPixmap& pixmap)
{
    QPainter painter(&pixmap);

    // Apply brush to the painter which draw shape
    painter.setBrush(_brush);

    // Apply pen to the painter which draw shape
    painter.setPen(_pen);

    // We calculate the radius
    int rx = _endPoint.x() - _startPoint.x();
    int ry = _endPoint.y() - _startPoint.y();

    // We draw the correct shape
    painter.drawEllipse(_startPoint.x(), _startPoint.y(), rx, ry);
}

void Circle::mousePressEvent(QMouseEvent* event)
{
    // We get the mouse position
    _startPoint = _endPoint = event->pos();
}

void Circle::mouseMoveEvent(QMouseEvent* event)
{
    // We update the mouse position
    _endPoint = event->pos();
}
