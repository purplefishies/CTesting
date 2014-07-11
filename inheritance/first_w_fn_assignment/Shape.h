#ifndef SHAPE_H
#define SHAPE_H

typedef struct _Shape Shape;


#define SHAPE_API_INTERFACE( T ) char *(*toStr)(T *);     \
    float (*Area)(T *);                                   \
    float (*Perimeter)(T *);

#define SHAPE_INTERFACE( T ) \
    Shape *base;             \
    SHAPE_API_INTERFACE( T )

typedef struct _Shape {
    SHAPE_API_INTERFACE(Shape);
} Shape;

Shape *new_Shape();


#endif
