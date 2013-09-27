#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QPixmap>
#include <QPen>
#include "mainwindow.h"
#include "defines.h"

class MainWindow;
class QPaintEvent;
class QMouseEvent;
class Shape;

class MyPainter : public QWidget
{
        Q_OBJECT
public:
    MyPainter(MainWindow* mainWindow);
    ~MyPainter();

    void resizeEvent(QResizeEvent* event);
    QPixmap getBuffer();
    QPixmap getBuffer2();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);

private:
    MainWindow* _mainWindow;
    QPixmap _buffer;
    QPixmap _buffer2;

    QPen _pen;
    QBrush _brush;
    QColor _windowBackgroundColor;
    QString _shapeToDraw;

    Shape* _shape;

    void deleteShape();

public slots:
    void erase();
    void shapeToDrawChange(QString newShapeToDraw);
    void colorToApplyChange(QString colorMenuWhichGenerateEvent, QColor color);
    void penStyleChange(QString newPenStyle);
    void sizeChange(int newSize);

protected slots:
    void shapeDrawed();
};

#endif // MYPAINTER_H
