#include "shape.h"

Shape::Shape(QPen &pen, QBrush &brush) :
    _pen(pen),
    _brush(brush),
    _drawed(false)
{
}

Shape::~Shape(){}

void Shape::mousePressEvent(QMouseEvent* event)
{

}

void Shape::mouseMoveEvent(QMouseEvent* event)
{

}

void Shape::mouseReleaseEvent(QMouseEvent* event)
{
    _drawed = true;
    emit drawed();
}

bool Shape::isDrawed()
{
    return _drawed;
}

QPen Shape::getPen()
{
    return this->_pen;
}

void Shape::setPen(QPen newPen)
{
    this->_pen = newPen;
}

QBrush Shape::getBrush()
{
    return this->_brush;
}

void Shape::setBrush(QBrush newBrush)
{
    this->_brush = newBrush;
}
