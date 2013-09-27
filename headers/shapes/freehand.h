#ifndef FREEHAND_H
#define FREEHAND_H

#include <QPoint>
#include "shape.h"

class FreeHand : public Shape
{
    Q_OBJECT

public:
    FreeHand(QPen& pen, QBrush& brush);
    ~FreeHand();

    void draw(QPixmap& pixmap);

private:
    QPoint _currentPoint;

public slots:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // FREEHAND_H
