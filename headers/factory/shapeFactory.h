#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "shape.h"

class ShapeFactory
{
public:
        enum PenStyle_enum{
            NoLine,
            SolidLine,
            DashLine,
            DotLine,
            DashDotLine,
            DashDotDotLine
        };

        enum Shape_enum{
            line,
            rectangle,
            circle,
            polygon,
            text
        };

        ShapeFactory();
        static Shape* createShape(Shape_enum shapeToDraw, QPen& pen, QBrush& brush);
};

#endif // SHAPEFACTORY_H