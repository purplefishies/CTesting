#ifndef BONUS_H
#define BONUS_H

#define BONUS_MIXIN( T ) \
    float (*bonus)(void *, float);

#define BONUS_INSTANTIATION( obj ) \
    obj->bonus = bonus;


extern float bonus( void *obj , float refval );


#endif
