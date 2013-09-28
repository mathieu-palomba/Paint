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

    // We set the rubber brush color (inside)
    _brush.setColor(Qt::white);

    // We set the rubber pen color (outline)
    _pen.setColor(Qt::white);
    _pen.setWidth(1);

    // Apply brush to the painter which draw shape
    painter.setBrush(_brush);

    // Apply pen to the painter which draw shape
    painter.setPen(_pen);

    // We calculate
    int rubberSize =_pen.width() + rubberOffset;

    painter.drawRect(_currentPoint.x() - (rubberSize/2), _currentPoint.y() - (rubberSize/2), rubberSize, rubberSize);
}

void Rubber::mousePressEvent(QMouseEvent* event)
{
    // We create the QPixmap wwich become the cursor
    QPixmap rubberCursor;

    // We load the picture in the QPixmap
    rubberCursor.load(":/rubber_icon");

    // We resize the QPixmap to the rubber size
    rubberCursor = rubberCursor.scaled(_pen.width() + rubberOffset, _pen.width() + rubberOffset);

    // We create the temporary cursor
    QApplication::setOverrideCursor(QCursor(rubberCursor));

    // We get the mouse position
    _currentPoint = event->pos();
}

void Rubber::mouseMoveEvent(QMouseEvent* event)
{
    // We update the mouse position
    _currentPoint = event->pos();
}

void Rubber::mouseReleaseEvent(QMouseEvent* event)
{
    // We create the normal cursor
    QApplication::restoreOverrideCursor();

    // We signal the shape it's drawed
    _drawed = true;
    emit drawed();
}
