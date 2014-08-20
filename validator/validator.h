#ifndef _VALIDATOR_H
#define _VALIDATOR_H

typedef int AIORET_TYPE;

#define SUCCESS                 0
#define INVALID_DATA           -1


#define VALIDATOR_INTERFACE(T)                                  \
    AIORET_TYPE (*Validate)( T*obj );                           \
    AIORET_TYPE (*ValidateChain)( T*obj );                      \
    AIORET_TYPE (*AddValidator)( T *self, T*next );             \
    void (*DeleteValidators)( T*top );                          \
    AIORET_TYPE (*NumberValidators)( T *self )                  \






typedef struct validator {
    VALIDATOR_INTERFACE( struct validator );
    struct validator *next;
} Validator;

AIORET_TYPE ValidateChain( struct validator *self );
void DeleteValidators( struct validator *tmp );
AIORET_TYPE NumberValidators( struct validator  *self );
struct validator *NewValidator( AIORET_TYPE (*validate_fn)( struct validator *obj ) );
AIORET_TYPE AddValidator( struct validator *self, struct validator *next );


#define VALIDATOR_MIXIN()   Validator validator;

#define MIXIN_VALIDATOR_ALLOCATOR( tmp, Validator )  memcpy( tmp, NewValidator(NULL) , sizeof(Validator))


#endif
