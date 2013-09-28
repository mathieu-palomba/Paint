#include <QInputDialog>
#include <QDebug>
#include "myPainter.h"
#include "shapes/shape.h"
#include "factory/shapeFactory.h"

const QString MyPainter::PEN_COLOR = "black";
const Qt::PenStyle MyPainter::PEN_STYLE = Qt::SolidLine;
const QString MyPainter::PEN_FILL_OUT_COLOR = "white";
const QString MyPainter::WINDOW_BACKGROUND_COLOR = "white";

MyPainter::MyPainter(MainWindow* mainWindow)
{
    _mainWindow = mainWindow;

    _shapeToDraw.append(tr("Free hand"));

    _windowBackgroundColor = QColor(WINDOW_BACKGROUND_COLOR);
    _pen.setColor(QColor(PEN_COLOR));
    _brush.setColor(QColor(PEN_FILL_OUT_COLOR));
    _pen.setStyle(PEN_STYLE);

    _buffer = QPixmap(_mainWindow->size());
    _buffer.fill(_windowBackgroundColor);           // Window background color

    _buffer2 = QPixmap(_buffer.size());
    _buffer2.fill(Qt::transparent);                 // Window background color
}

MyPainter::~MyPainter()
{
}

void MyPainter::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton){
        qDebug("Mouse pressed");

        // We check if the fill out color it's the same like background color to disable brush (fill out it's transparent)
        _brush.setStyle(Qt::NoBrush);
        if(_windowBackgroundColor != _brush.color()){
            _brush.setStyle(Qt::SolidPattern);
        }

        deleteShape();

        if ( !_shape )
        {
            // Create the shape to draw
            if(_shapeToDraw == tr("&Line")){
                _shape = ShapeFactory::createShape(ShapeFactory::line, _pen, _brush);
            }
            else if(_shapeToDraw == tr("Rectangle")){
                _shape = ShapeFactory::createShape(ShapeFactory::rectangle, _pen, _brush);
            }
            else if(_shapeToDraw == tr("Circle")){
                _shape = ShapeFactory::createShape(ShapeFactory::circle, _pen, _brush);
            }
            else if(_shapeToDraw == tr("Polygon")){
                _shape = ShapeFactory::createShape(ShapeFactory::polygon, _pen, _brush);
            }
            else if(_shapeToDraw == tr("Text")){
                _shape = ShapeFactory::createShape(ShapeFactory::text, _pen, _brush);
            }
            else if(_shapeToDraw == tr("Free hand")){
                _shape = ShapeFactory::createShape(ShapeFactory::freeHand, _pen, _brush);
            }
            else if(_shapeToDraw == tr("Rubber")){
                _shape = ShapeFactory::createShape(ShapeFactory::rubber, _pen, _brush);
            }

            if( _shape )
            {
                qDebug() << "Shape " << _shapeToDraw << " created";
                connect( _shape, SIGNAL(drawed()), this, SLOT(shapeDrawed()));
            }
        }
        else
        {
            qDebug() << "A shape already exist";
        }

        // Generate the mouse event to the shape
        if( _shape )
        {
            _shape->mousePressEvent( event );
            qDebug("Press send");
        }
    }
}

void MyPainter::mouseMoveEvent(QMouseEvent* event)
{
    if (event->type() == QEvent::MouseMove)
    {
        qDebug("Mouse move");

        // We clear the buffer without instanciate again
        _buffer2.fill( Qt::transparent );

        // If the shape exist (the factory doesn't return NULL)
        if( _shape )
        {
            qDebug("Move event");
            // Generate the mouse event to the shape (update the _endPoint)
            _shape->mouseMoveEvent( event );

            // We draw the shape into the buffer
            if(_shapeToDraw == tr("Rubber"))    _shape->draw( _buffer );
            else                                _shape->draw( _buffer2 );

            qDebug("Moved event");
        }

        // We call the paintEvent method
        update();   // Update your view
    }
}

void MyPainter::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton){
        qDebug("Mouse release");

        if( _shape )
        {
            qDebug("Release event");
            _buffer2.fill( Qt::transparent );
            _shape->draw( _buffer2 );

            _shape->mouseReleaseEvent( event );
            qDebug("Released event");
        }

        // We call the paintEvent method
        update();

        deleteShape();
    }
}

void MyPainter::paintEvent(QPaintEvent* event)
{
    qDebug("Paint window in paint event");
    QPainter paintWindow(this);

    paintWindow.drawPixmap(0, 0, _buffer);          // Draw the pixmap at the position (x, y)

    if(_shape)
    {
        qDebug("Paint event");
        paintWindow.drawPixmap(0, 0, _buffer2);     // Draw the pixmap at the position (x, y)
        qDebug("Painted event");
    }
}

void MyPainter::shapeDrawed()
{
    if( _shape )
    {
        qDebug("shapeDraw event");
        _buffer2.fill( Qt::transparent );
        _shape->draw( _buffer2 );
        qDebug("shapeDrawed event");
    }
}

void MyPainter::deleteShape()
{
    if( _shape )
    {
        if( _shape->isDrawed() )
        {
            qDebug()<< "Draw finish";
            // If the shape exist (the factory doesn't return NULL)
            if( _shape )
            {
                // Generate the mouse event to the shape
                qDebug("end draw");
                _shape->draw( _buffer );

                qDebug() << "delete";
                disconnect( _shape, SIGNAL(drawed()), this, SLOT(shapeDrawed()));
                delete _shape;
            }

            _shape = NULL;
        }
    }
}

void MyPainter::eraseScreen()
{
    _buffer = QPixmap(_mainWindow->size());
    _buffer.fill(_windowBackgroundColor);           // Window background color

    _buffer2 = QPixmap(_buffer.size());
    _buffer2.fill(Qt::transparent);                 // Window background color

    if( _shape )
    {
        disconnect( _shape, SIGNAL(drawed()), this, SLOT(shapeDrawed()));

        delete _shape;
        _shape = NULL;
    }

    qDebug("update after erase");

    update();
}

void MyPainter::shapeToDrawChange(QString newShapeToDraw)
{
    _shapeToDraw.clear();
    _shapeToDraw.append(newShapeToDraw);
}

void MyPainter::colorToApplyChange(QString colorMenuWhichGenerateEvent, QColor color)
{
    // Shape color
    if(colorMenuWhichGenerateEvent == tr("Changed shape color")){
        _pen.setColor(color);
    }

    // Fill out color
    else if(colorMenuWhichGenerateEvent == tr("Changed fill Color"))
    {
        _brush.setColor(color);
    }
}

void MyPainter::penStyleChange(QString newPenStyle)
{
    if(newPenStyle == tr("Solid line"))             _pen.setStyle(Qt::SolidLine);
    else if(newPenStyle == tr("Dash line"))         _pen.setStyle(Qt::DashLine);
    else if(newPenStyle == tr("Dot line"))          _pen.setStyle(Qt::DotLine);
    else if(newPenStyle == tr("Dash dot line"))     _pen.setStyle(Qt::DashDotLine);
    else if(newPenStyle == tr("Dash dot dot line")) _pen.setStyle(Qt::DashDotDotLine);
}

void MyPainter::sizeChange(int newSize)
{
    _pen.setWidth(newSize);
}

void MyPainter::resizeEvent(QResizeEvent* event)
{
    /*qDebug("Resize %d %d", this->size().width(), this->size().height());
    // Peut etre utiliser save et restore?
this->_buffer = this->_buffer.scaled(this->size().width(), this->size().height());//, Qt::KeepAspectRatio);
this->_buffer2 = this->_buffer2.scaled(this->size().width(), this->size().height());//, Qt::KeepAspectRatio);*/
}

QPixmap& MyPainter::getBuffer()
{
    return this->_buffer;
}
