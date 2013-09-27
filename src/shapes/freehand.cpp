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
    painter.drawPoint(_currentPoint);
}

void FreeHand::mousePressEvent(QMouseEvent* event)
{
    _currentPoint = event->pos();
    _drawed = false;
}

void FreeHand::mouseMoveEvent(QMouseEvent* event)
{
    _currentPoint = event->pos();
    _drawed = true;
    emit drawed();
}
