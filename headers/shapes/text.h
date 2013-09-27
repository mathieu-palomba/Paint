#ifndef TEXT_H
#define TEXT_H

#include <QPoint>
#include "shape.h"

class Text : public Shape
{
    Q_OBJECT

public:
    Text(QPen &pen, QBrush &brush);
    ~Text();

    void draw(QPixmap& pixmap);

private:
    QPoint _startPoint;
    QString _textToDisplay;

public slots:
    void mousePressEvent(QMouseEvent* event);
};

#endif // TEXT_H
