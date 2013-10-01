#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QPixmap>
#include <QPen>
#include "window/mainwindow.h"

class MainWindow;
class QPaintEvent;
class QMouseEvent;
class Shape;

class MyPainter : public QWidget
{
    Q_OBJECT

    static const QString PEN_COLOR;
    static const Qt::PenStyle PEN_STYLE;
    static const Qt::BrushStyle BRUSH_STYLE;
    static const QString PEN_FILL_OUT_COLOR;
    static const QString WINDOW_BACKGROUND_COLOR;

public:
    MyPainter(MainWindow* mainWindow);
    ~MyPainter();

    void resizeEvent(QResizeEvent* event);
    QPixmap& getBuffer();

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
    Qt::BrushStyle _brushStyle;
    QColor _windowBackgroundColor;
    QString _shapeToDraw;

    Shape* _shape;

    void deleteShape();

public slots:
    void eraseScreen();
    void shapeToDrawChange(QString newShapeToDraw);
    void colorToApplyChange(QString colorMenuWhichGenerateEvent, QColor color);
    void penStyleChange(QString newPenStyle);
    void brushStyleChange(Qt::BrushStyle newBrushStyle);
    void sizeChange(int newSize);

protected slots:
    void shapeDrawed();
};

#endif // MYPAINTER_H
