#include "freehand.h"

FreeHand::FreeHand(QPen& pen, QBrush& brush) :
    Shape(pen, brush)
{
}

FreeHand::~FreeHand()
{
}

void FreeHand::draw(QPixmap& pixmap)
{
    QPainter painter(&pixmap);

    // Apply brush to the painter which draw shape
    painter.setBrush(_brush);

    // Apply pen to the painter which draw shape
    painter.setPen(_pen);

    // We draw all of the points
    for(int i=0; i<_points.size(); i++)
    {
        painter.drawPoint(_points.at(i));
    }
}

void FreeHand::mousePressEvent(QMouseEvent* event)
{
    // We get the mouse position
    _points.push_back(event->pos());
}

void FreeHand::mouseMoveEvent(QMouseEvent* event)
{
    // We update the mouse position
    _points.push_back(event->pos());
}
