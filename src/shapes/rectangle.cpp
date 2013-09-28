#include "rectangle.h"
#include <QBrush>

Rectangle::Rectangle(QPen& pen, QBrush& brush) :
    Shape(pen, brush)
{
}

Rectangle::~Rectangle()
{
}

void Rectangle::draw(QPixmap& pixmap)
{
    QPainter painter(&pixmap);

    // Apply brush to the painter which draw shape
    painter.setBrush(_brush);

    // Apply pen to the painter which draw shape
    painter.setPen(_pen);

    // We draw the correct shape
    painter.drawRect(QRect(_startPoint, _endPoint));
}

void Rectangle::mousePressEvent(QMouseEvent* event)
{
    _startPoint = _endPoint = event->pos();
}

void Rectangle::mouseMoveEvent(QMouseEvent* event)
{
    _endPoint = event->pos();
}
