#include <math.h>
#include "shapes/polygon.h"

// Initialize the delta value
const int Polygon::delatEnd = 5;

Polygon::Polygon(QPen& pen, QBrush& brush) :
    Shape(pen, brush)
{
}

Polygon::~Polygon()
{
}

void Polygon::draw(QPixmap& pixmap)
{
    QPainter painter(&pixmap);

    // Apply brush to the painter which draw shape
    painter.setBrush(_brush);

    // Apply pen to the painter which draw shape
    painter.setPen(_pen);

    if( ! _points.empty() )
    {
        if( !_drawed )
        {
            painter.drawEllipse(_points.at(0), delatEnd, delatEnd);
        }

        QPolygon myPolygon( _points );

        myPolygon.append( _movPoint );
        painter.drawPolygon(myPolygon);
    }

}

void Polygon::mousePressEvent(QMouseEvent* event)
{
    // If the user click for the first time, we get the first point
    if( _points.empty() )
    {
        // We get the mouse position
        _movPoint = event->pos();
        _points.push_back( _movPoint );

        _drawed = false;
    }

    // We check if the next click it's in the circle arround the first point
    else
    {
        // We get the first point
        QPoint begin = _points.at(0);

        // We calcul delta arround the first point
        double delta = sqrt( ( begin.x() - event->pos().x() ) * ( begin.x() - event->pos().x() ) +
                 ( begin.y() - event->pos().y() ) * ( begin.y() - event->pos().y() ) );

        // If the user click outside the circle arround the first point, we save the new point
        if( delta > delatEnd )
        {
            _points.push_back( event->pos() );
        }

        // We signal the shape it's drawed
        else
        {
            _drawed = true;
            emit drawed();
        }
    }
}

void Polygon::mouseMoveEvent( QMouseEvent* event )
{
    // We update the mouse position
    _movPoint = event->pos();
}

void Polygon::mouseReleaseEvent(QMouseEvent* event)
{
    // Do nothing here because the shape it's drawed when the user click in the circle arround the first point
}

