#ifndef FREEHAND_H
#define FREEHAND_H

#include <QPoint>
#include "shapes/shape.h"

class FreeHand : public Shape
{
    Q_OBJECT

public:
    FreeHand(QPen& pen, QBrush& brush);
    ~FreeHand();

    void draw(QPixmap& pixmap);

private:
    QVector<QPoint> _points;

public slots:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // FREEHAND_H
