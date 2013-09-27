#include "line.h"

Line::Line(QPen &pen, QBrush &brush) :
    Shape(pen, brush)
{
}

Line::~Line()
{
}

void Line::draw(QPixmap& pixmap)
{
    QPainter painter(&pixmap);
    painter.setBrush(_brush);

    // Apply pen to the painter which draw shape
    painter.setPen(_pen);

    // We draw the correct shape
    painter.drawLine(_startPoint, _endPoint);
}

void Line::mousePressEvent(QMouseEvent* event)
{
    _startPoint = _endPoint = event->pos();
}

void Line::mouseMoveEvent(QMouseEvent* event)
{
    _endPoint = event->pos();
}
