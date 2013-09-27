#include "circle.h"

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
    painter.setBrush(_brush);

    // Apply pen to the painter which draw shape
    painter.setPen(_pen);

    // We draw the correct shape
    int rx = _endPoint.x() - _startPoint.x();
    int ry = _endPoint.y() - _startPoint.y();
    painter.drawEllipse(_startPoint.x(), _startPoint.y(), rx, ry);
}

void Circle::mousePressEvent(QMouseEvent* event)
{
    _startPoint = _endPoint = event->pos();
}

void Circle::mouseMoveEvent(QMouseEvent* event)
{
    _endPoint = event->pos();
}
