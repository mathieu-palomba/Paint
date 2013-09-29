#include <QtGui/QApplication>
#include "window/mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QGraphicsScene scene;
    //scene.setForegroundBrush(QBrush(Qt::blue));
    //scene.setBackgroundBrush(QBrush(Qt::red));

    QGraphicsRectItem* rectItem = scene.addRect(QRectF(0,0,100,100));
    rectItem->setFlag(QGraphicsItem::ItemIsMovable);    // To accept movable shape

    QPen pen;
    pen.setColor(Qt::red);
    pen.setStyle(Qt::DashDotLine);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);   // To allow fill out color
    brush.setColor(Qt::green);          // Fill out color

    rectItem->setPen(pen);              // Apply outline color
    rectItem->setBrush(brush);          // Apply fill out color

    //qDebug() << scene.items();        // Display all of the shape into the scene

    QGraphicsView view(&scene);
    view.show();

    //QPixmap pixMap = QPixmap::grabWidget(view);   // Create a pixmap to load and save picture (png, jpg...)

    return a.exec();
}
