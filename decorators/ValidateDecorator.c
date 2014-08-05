#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct validator {
    struct validator *(*validate)( struct validator *obj , int *result );
    struct validator *self;
    int x;
    int y;
} Validator;

struct validator *validate( struct validator *obj , int *result ) {
    if ( abs(abs(obj->x) - abs(obj->y)) < 4 ) {
        return obj;
    } else {
        *result = 3;
        return NULL;
    }
}

Validator *NewValidator( int x, int y ) {
    Validator *tmp = (Validator *)calloc(sizeof(Validator),1);
    tmp->x = x;
    tmp->y = y;
    tmp->validate = validate;
    return tmp;
}

/* typedef struct validator2 { */
/*     struct validator *(*validate)( struct validator *obj , int *result ); */
/*     struct validator *self; */
/*     int x; */
/*     int y; */
/*     /\* Validator tmp; *\/ */
/* } Validator2; */

struct validator *other_validate( struct validator *obj , int *result ) 
{
    struct validator *tmp = obj->self->validate( obj->self, result );
    if( tmp && *result  == 0 ) {
        if ( obj->x*obj->x + obj->y * obj->y > 8 ) {
            *result = 4;
            return NULL;
        } else {
            return obj;
        }
    } else {
        return NULL;
    }
}

Validator *NewValidator2( Validator *obj ) 
{
    Validator *tmp = (Validator*)calloc(sizeof(Validator),1);
    tmp->self = obj;
    tmp->x    = obj->x;
    tmp->y    = obj->y;
    tmp->validate = other_validate;
}

struct validator *both_odd_validate( struct validator *obj , int *result ) 
{
    struct validator *tmp = obj->self->validate( obj->self, result );
    if( tmp && *result  == 0 ) {
        if ( obj->x % 2 == 1 && obj->y % 2 == 1 ) { /* both or odd */
            return obj;
        } else {
            *result = 5;
            return NULL;
        }
    } else {
        return NULL;
    }
}

Validator *OddValidator( Validator *obj ) 
{
    Validator *tmp = (Validator*)calloc(sizeof(Validator),1);
    tmp->self = obj;
    tmp->x    = obj->x;
    tmp->y    = obj->y;
    tmp->validate = both_odd_validate;
}

/* #define CHECK(...)  */
#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(__VA_ARGS__, 7,6,5,4,3,2,1)
#define VA_NUM_ARGS_IMPL(_1,_2,_3,_4,_5,_6,_7,N,...) N

#define CHECK(...)  CHECK_ARGS4( VA_NUM_ARGS(__VA_ARGS__) ( __VA_ARGS__, 7,6,5,4,3,2,1)
#define CHECK_ARGS5( a, b, c, d, e, f ) CHECK_ARGS4( a, b, c , d , e ( f ) ) )
#define CHECK_ARGS4( a, b, c, d, e ) CHECK_ARGS3( a, b, c , d ( e  ) )
#define CHECK_ARGS3( a, b, c, d )   CHECK_ARGS2( a, b, c( d ) )
#define CHECK_ARGS2( a, b ,c )   MAKE_ARG(a, b( c ) )
#define MAKE_ARG( a, b )  ( tmp = b  )->validate( tmp, a )

/* (tmp = OddValidator( NewValidator2( NewValidator(-1,1)  )  )   )->validate( tmp, &result ); */
/* #define CHECK_ARGS(_1,_2,_3,_4,_5,_6,_7, N ,...) (tmp = N  )  ->validate( tmp, _1 ) */

#define BLAH VA_NUM_ARGS(x,y,z,f,ff,as,zz)

int 
main(int argc, char *argv ) 
{
    char *buf = NULL;
    asprintf(&buf, "%d", BLAH );
    printf("%s\n", buf );
    Validator *tmp = NewValidator(2,4);
    int result = 0;
    if( tmp->validate( tmp , &result ) ) {
        printf("Was good\n");
    }  else {
        printf("was bad: %d\n", result );
    }
    tmp = NewValidator(2,6);
    if( tmp->validate( tmp , &result ) ) {
        printf("Was good\n");
    }  else {
        printf("was bad: %d\n", result );
    }
    result = 0;

    tmp = NewValidator2( NewValidator(4,6) );

    if( tmp->validate( tmp , &result ) ) {
        printf("Was good\n");
    }  else {
        printf("was bad: %d\n", result );
    }

    result = 0;
    (tmp = OddValidator( NewValidator2( NewValidator(-1,1)  )  )   )->validate( tmp, &result );

    /**
     * Better would be 
     *
     * validator( &result, obj, 3 , OddValidator, NewValidator2, NewValidator1 );
     *
     *
     *
     */

    if( result == 0 ) {
        printf("Was good\n");
    } else {
        printf("was bad: %d\n", result );
    }
}


/* CHECK_ARGS( &result, OddValidator, NewValidator,  dev ); */
/* [ OddValidator, NewValidator, dev ] */
/* CHECK( &result,  OddValidator , NewValidator2, (NewValidator(-1,1)) ); */
/* MAKE_ARG( &result, NewValidator(-1,1) ); */
/* CHECK_ARGS3( &result, OddValidator , NewValidator2, NewValidator(-1,1)); */

/* goal is to have 
 */
/* void *tmp = NewDIOValidatorRange( NewDIOValidatorValidDIO( NewValidatorRangeValues( dev ))); */
/* result = tmp->validator( tmp ); */
/* if ( result != AIOUSB_SUCCESS )  */
/*     return ERROR; */
/* #define VALIDATORER_INTERFACE(T)                       \ */
/*     typedef struct T {                             \ */
/*         void (*validator)( struct T *obj );            \ */
/*         Validatorer *self;                             \ */
/*         int x,y;                                   \ */
/*     } T; */
/* typedef struct validatorer { */
/*     void (*validator)( struct validatorer *obj ); */
/*     Validatorer *self; */
/*     int x, y; */
/* } Validatorer; */
/* VALIDATORER_INTERFACE(Validatorer); */
/* VALIDATORER_INTERFACE(NewValidatorer); */
/* VALIDATORER_INTERFACE(CoolDecorator); */
