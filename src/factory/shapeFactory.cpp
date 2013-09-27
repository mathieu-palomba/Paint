#include "shapeFactory.h"
#include "freehand.h"
#include "line.h"
#include "rectangle.h"
#include "circle.h"
#include "polygon.h"
#include "text.h"

ShapeFactory::ShapeFactory()
{
}

Shape* ShapeFactory::createShape(Shape_enum shapeToDraw, QPen &pen, QBrush &brush)
{
    if(shapeToDraw == line)
    {
        return new Line(pen, brush);
    }

    else if(shapeToDraw == rectangle)
    {
        return new Rectangle(pen, brush);
    }

    else if(shapeToDraw == circle)
    {
        return new Circle(pen, brush);
    }

    else if(shapeToDraw == polygon)
    {
        return new Polygon(pen, brush);
    }

    else if(shapeToDraw == text)
    {
        return new Text(pen, brush);
    }

    else if(shapeToDraw == freeHand)
    {
        return new FreeHand(pen, brush);
    }

    return NULL;
}
