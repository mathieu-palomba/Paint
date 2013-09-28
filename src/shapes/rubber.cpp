#include "rubber.h"

const int Rubber::rubberHeight = 10;
const int Rubber::rubberWidth = 10;

Rubber::Rubber(QPen& pen, QBrush& brush) :
    Shape(pen, brush)
{
}

Rubber::~Rubber()
{
}

void Rubber::draw(QPixmap& pixmap)
{
    QPainter painter(&pixmap);

    //_brush.setColor(Qt::black);

    painter.setBrush(_brush);

    _pen.setWidth(1);
    _pen.setColor(Qt::blue);

    // Apply pen to the painter which draw shape
    painter.setPen(_pen);

    // We draw the correct shape
    int rubberSize =_pen.width()+10;
    painter.drawRect(_currentPoint.x()-rubberSize, _currentPoint.y()-rubberSize, rubberSize, rubberSize);
}

void Rubber::mousePressEvent(QMouseEvent* event)
{
    _currentPoint = event->pos();
}

void Rubber::mouseMoveEvent(QMouseEvent* event)
{
    _currentPoint = event->pos();
}
