#include "Rectangle.h"
#include <stdlib.h>
#include <stdio.h>

char *Rectangle_toStr(Rectangle *self) { 
    static char buf[64];
    sprintf(buf,"w:%f, h:%f", self->width,self->height );
    return buf;
}

float Rectangle_Area(Rectangle *self) {
    float retval;
    return self->width * self->height;
}

float Rectangle_Perimeter(Rectangle *self) {
    return 2*self->width + 2*self->height;
}

Rectangle *new_Rectangle( float width, float height ) {
    Rectangle *obj = (Rectangle *)malloc(sizeof(Rectangle));
    obj->base = new_Shape();
    obj->width = width;
    obj->height = height;
    obj->Area = Rectangle_Area;
    obj->Perimeter = Rectangle_Perimeter;
    obj->toStr = Rectangle_toStr;
}
