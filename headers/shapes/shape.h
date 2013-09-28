#ifndef SHAPE_H
#define SHAPE_H

#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <qnamespace.h>
#include <qpen.h>

class Shape : public QObject
{
    Q_OBJECT

public:
    Shape(QPen& pen, QBrush& brush);
    virtual ~Shape();

    virtual void draw(QPixmap& pixmap) = 0;

    QPen getPen();
    void setPen(QPen newPen);

    QBrush getBrush();
    void setBrush(QBrush newBrush);

    bool isDrawed();

signals:
    void drawed();

protected:
    QPen _pen;
    QBrush _brush;
    bool _drawed;

public slots:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
};

#endif // SHAPE_H
