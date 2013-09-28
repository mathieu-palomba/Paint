#include "shapeFactory.h"
#include "freehand.h"
#include "line.h"
#include "rectangle.h"
#include "circle.h"
#include "polygon.h"
#include "text.h"
#include "rubber.h"

ShapeFactory::ShapeFactory()
{
}

Shape* ShapeFactory::createShape(Shape_enum shapeToDraw, QPen &pen, QBrush &brush)
{
    // We return a Line
    if(shapeToDraw == line)
    {
        return new Line(pen, brush);
    }

    // We return a Rectangle
    else if(shapeToDraw == rectangle)
    {
        return new Rectangle(pen, brush);
    }

    // We return a Circle
    else if(shapeToDraw == circle)
    {
        return new Circle(pen, brush);
    }

    // We return a Polygon
    else if(shapeToDraw == polygon)
    {
        return new Polygon(pen, brush);
    }

    // We return a Text
    else if(shapeToDraw == text)
    {
        return new Text(pen, brush);
    }

    // We return a FreeHand
    else if(shapeToDraw == freeHand)
    {
        return new FreeHand(pen, brush);
    }

    // We return a Rubber
    else if(shapeToDraw == rubber)
    {
        return new Rubber(pen, brush);
    }

    // We don't return a shape
    return NULL;
}
