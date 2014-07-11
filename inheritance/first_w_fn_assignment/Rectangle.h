#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"


typedef struct _Rectangle Rectangle;

#define RECTANGLE_INTERFACE                       \
    SHAPE_INTERFACE( Rectangle );                 \
    float width, height;

typedef struct _Rectangle { 
   RECTANGLE_INTERFACE;
} Rectangle;

Rectangle *new_Rectangle( float width, float height );



#endif
