#include "polygon.h"
#include "math.h"

// Initialize the delta value
const int Polygon::delatEnd = 5;

Polygon::Polygon(QPen& pen, QBrush& brush) :
    Shape(pen, brush)
{
}

Polygon::~Polygon()
{
    qDebug() << "polygon destroyed";
}

void Polygon::draw(QPixmap& pixmap)
{
    QPainter painter(&pixmap);
    painter.setBrush(_brush);

    // Apply pen to the painter which draw shape
    painter.setPen(_pen);

    for( int i = 0; i < _points.size(); ++i )
    {
        qDebug() << _points.at(i);
    }

    if( ! _points.empty() )
    {
        if( !_drawed )
            painter.drawEllipse(_points.at(0), delatEnd, delatEnd);
        //else
        //    _points.push_back( _points.at(0));

        QPolygon myPolygon( _points );
        myPolygon.append( _movPoint );
        painter.drawPolygon(myPolygon);
    }

}

void Polygon::mousePressEvent(QMouseEvent* event)
{
    if( _points.empty() )
    {
        _points.push_back( event->pos() );
        _movPoint = event->pos();
        _drawed = false;
    }
    else
    {
        QPoint begin = _points.at(0);
        double delta = sqrt( ( begin.x() - event->pos().x() ) * ( begin.x() - event->pos().x() ) +
                 ( begin.y() - event->pos().y() ) * ( begin.y() - event->pos().y() ) );
        if( delta > delatEnd )
        {
            _points.push_back( event->pos() );
        }
        else
        {
            _drawed = true;
            emit drawed();
        }
    }
}

void Polygon::mouseMoveEvent( QMouseEvent* event )
{
    _movPoint = event->pos();
}

void Polygon::mouseReleaseEvent(QMouseEvent* event)
{

}

