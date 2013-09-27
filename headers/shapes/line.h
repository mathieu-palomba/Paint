#ifndef LINE_H
#define LINE_H

#include <QPoint>
#include "shape.h"

class Line : public Shape
{
    Q_OBJECT

public:
    Line(QPen& pen, QBrush& brush);
    ~Line();

    void draw(QPixmap& pixmap);

private:
    QPoint _startPoint, _endPoint;

public slots:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // LINE_H
