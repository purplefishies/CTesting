#include <stdio.h>
#include "Rectangle.h"
#include "Shape.h"

int
main(int argc, char *argv ) {
    Shape *nshape;
    Rectangle *rect = new_Rectangle(3.3, 4.2 );
    printf("Rect: %s\n", rect->toStr(rect) );
    printf("Area: %f\n", rect->Area(rect) );
    printf("Perimeter: %f\n", rect->Perimeter(rect) );

}
