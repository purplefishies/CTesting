#include "Shape.h"
#include <stdlib.h>

char *toStr(Shape *self) 
{
    return "Null";
}

float Area(Shape *self) { 
    return 0.0;
}

float Perimeter(Shape *self) { 
    return 0.0;
}

Shape *new_Shape() {
    Shape *obj = (Shape *)malloc(sizeof(Shape));
    obj->toStr = toStr;
    obj->Area  = Area;
    obj->Perimeter = Perimeter;
    return obj;
}

