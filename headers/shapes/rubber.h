#ifndef RUBBER_H
#define RUBBER_H

#include <QPoint>
#include "shape.h"

class Rubber : public Shape
{
    static const int rubberHeight;
    static const int rubberWidth;

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
};

#endif // RUBBER_H
