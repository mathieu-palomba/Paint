#ifndef POLYGON_H
#define POLYGON_H

#include <QPoint>
#include "shape.h"

class Polygon : public Shape
{
    Q_OBJECT

    static const int delatEnd;  // Space around the first start point, that significant the user end to draw the polygon

public:
    Polygon(QPen &pen, QBrush &brush);
    ~Polygon();

    void draw(QPixmap& pixmap);

private:
    QVector<QPoint> _points;
    QPoint _movPoint;

public slots:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
};

#endif // POLYGON_H
