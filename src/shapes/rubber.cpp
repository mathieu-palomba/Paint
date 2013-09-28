#include "rubber.h"
#include <QApplication>

const int Rubber::rubberOffset = 10;

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

    _brush.setColor(Qt::black);

    painter.setBrush(_brush);

    _pen.setWidth(1);
    _pen.setColor(Qt::white);

    // Apply pen to the painter which draw shape
    painter.setPen(_pen);

    // We draw the correct shape
    int rubberSize =_pen.width() + rubberOffset;
    painter.drawRect(_currentPoint.x(), _currentPoint.y(), rubberSize, rubberSize);
}

void Rubber::mousePressEvent(QMouseEvent* event)
{
    QPixmap rubberCursor;
    rubberCursor.load(":/rubber_icon");
    rubberCursor = rubberCursor.scaled(_pen.width() + rubberOffset, _pen.width() + rubberOffset);

    QApplication::setOverrideCursor(QCursor(rubberCursor));

    _currentPoint = event->pos();
}

void Rubber::mouseMoveEvent(QMouseEvent* event)
{
    _currentPoint = event->pos();
}

void Rubber::mouseReleaseEvent(QMouseEvent* event)
{
    QApplication::restoreOverrideCursor();

    _drawed = true;
    emit drawed();
}
