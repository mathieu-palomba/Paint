#ifndef RUBBER_H
#define RUBBER_H

#include <QPoint>
#include "shapes/shape.h"

class Rubber : public Shape
{
    static const int rubberOffset;

    Q_OBJECT

public:
    Rubber(QPen& pen, QBrush& brush);
    ~Rubber();

    void draw(QPixmap& pixmap);

private:
    QPoint _currentPoint;

public slots:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
};

#endif // RUBBER_H
