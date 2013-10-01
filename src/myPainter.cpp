#include <QInputDialog>
#include <QDebug>
#include <QMessageBox>
#include "myPainter.h"
#include "shapes/shape.h"
#include "factory/shapeFactory.h"

// Initialize the defaults parameters
const ShapeFactory::Shape_enum MyPainter::DEFAULT_SHAPE =               ShapeFactory::freeHand;
const QString MyPainter::PEN_COLOR =                                    "black";
const Qt::PenStyle MyPainter::PEN_STYLE =                               Qt::SolidLine;
const Qt::BrushStyle MyPainter::BRUSH_STYLE =                           Qt::SolidPattern;
const QString MyPainter::PEN_FILL_OUT_COLOR =                           "white";
const QString MyPainter::WINDOW_BACKGROUND_COLOR =                      "white";

MyPainter::MyPainter(MainWindow* mainWindow):
_shape(NULL)
{
    _mainWindow = mainWindow;

    _shapeToDraw = DEFAULT_SHAPE;

    _windowBackgroundColor = QColor(WINDOW_BACKGROUND_COLOR);
    _pen.setColor(QColor(PEN_COLOR));
    _brush.setColor(QColor(PEN_FILL_OUT_COLOR));
    _pen.setStyle(PEN_STYLE);
    _brushStyle = BRUSH_STYLE;

    _buffer = QPixmap(_mainWindow->size());
    _buffer.fill(_windowBackgroundColor);           // Window background color

    _buffer2 = QPixmap(_buffer.size());
    _buffer2.fill(Qt::transparent);                 // Window background color

    this->setFixedSize(_mainWindow->size());
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
            _brush.setStyle(_brushStyle);
        }

        deleteShape();

        if ( !_shape )
        {
            // Create the shape to draw
            _shape = ShapeFactory::createShape(_shapeToDraw, _pen, _brush);

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
            qDebug("Mouse press sended to the shape");
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
            // Generate the mouse event to the shape (update the _endPoint)
            _shape->mouseMoveEvent( event );

            // We draw the shape into the buffer
            if(_shapeToDraw == ShapeFactory::rubber)    _shape->draw( _buffer );
            else                                        _shape->draw( _buffer2 );

            qDebug("Mouse move sended to the shape");
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
            _buffer2.fill( Qt::transparent );
            _shape->draw( _buffer2 );

            _shape->mouseReleaseEvent( event );
            qDebug("Mouse released sended to the shape");
        }

        // We call the paintEvent method
        update();

        deleteShape();
    }
}

void MyPainter::paintEvent(QPaintEvent* event)
{
    qDebug("Paint window");
    QPainter paintWindow(this);

    paintWindow.drawPixmap(0, 0, _buffer);          // Draw the pixmap at the position (x, y)

    if(_shape)
    {
        paintWindow.drawPixmap(0, 0, _buffer2);     // Draw the pixmap at the position (x, y)
    }
}

void MyPainter::shapeDrawed()
{
    if( _shape )
    {
        _buffer2.fill( Qt::transparent );
        _shape->draw( _buffer2 );

        qDebug("Shape drawed");
    }
}

void MyPainter::deleteShape()
{
    if( _shape )
    {
        if( _shape->isDrawed() )
        {
            qDebug("Draw finish");

            // If the shape exist (the factory doesn't return NULL)
            if( _shape )
            {
                // Generate the mouse event to the shape
                qDebug("Last draw");
                _shape->draw( _buffer );

                disconnect( _shape, SIGNAL(drawed()), this, SLOT(shapeDrawed()));
                delete _shape;

                qDebug() << "Shape deleted";
            }

            _shape = NULL;
        }
    }
}

void MyPainter::eraseScreen(bool force)
{
    int response = QMessageBox::Yes;

    if( ! force )
        response = QMessageBox::question(this, tr("Paint"), tr("Do you really want to erase you're drawing?"), QMessageBox::Yes|QMessageBox::No);

    // If the user want to erase her drawing
    if (response == QMessageBox::Yes){
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

        update();
    }
}

void MyPainter::shapeToDrawChange(ShapeFactory::Shape_enum newShapeToDraw)
{
    _shapeToDraw = newShapeToDraw;
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

void MyPainter::penStyleChange(Qt::PenStyle newPenStyle)
{
    _pen.setStyle(newPenStyle);
}

void MyPainter::brushStyleChange(Qt::BrushStyle newBrushStyle)
{
    _brushStyle = newBrushStyle;
}

void MyPainter::sizeChange(int newSize)
{
    _pen.setWidth(newSize);
}

/*void MyPainter::resizeEvent(QResizeEvent* event)
{
    /*qDebug("Resize %d %d", this->size().width(), this->size().height());
    // Peut etre utiliser save et restore?
this->_buffer = this->_buffer.scaled(this->size().width(), this->size().height());//, Qt::KeepAspectRatio);
this->_buffer2 = this->_buffer2.scaled(this->size().width(), this->size().height());//, Qt::KeepAspectRatio);*/
//}

QPixmap& MyPainter::getBuffer()
{
    return this->_buffer;
}
