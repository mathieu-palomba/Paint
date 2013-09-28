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
    painter.setBrush(_brush);

    // Apply pen to the painter which draw shape
    painter.setPen(_pen);

    qDebug() << "draw free hand" << _pen.color() << " " << painter.brush().color();

    // We draw the correct shape
    for(int i=0; i<_points.size(); i++)
    {
        painter.drawPoint(_points.at(i));
    }
}

void FreeHand::mousePressEvent(QMouseEvent* event)
{
    _points.push_back(event->pos());
}

void FreeHand::mouseMoveEvent(QMouseEvent* event)
{
    _points.push_back(event->pos());
}
