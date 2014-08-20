#ifndef _VALIDATOR_H
#define _VALIDATOR_H

typedef int AIORET_TYPE;

#define SUCCESS                 0
#define INVALID_DATA           -1


#define VALIDATOR_INTERFACE(T)                                          \
    AIORET_TYPE (*Validate)( T*obj );                                   \
    AIORET_TYPE (*ValidateChain)( T*obj );                              \
    AIORET_TYPE (*AddValidator)( T *self, struct validator *next );     \
    void (*DeleteValidators)( T*top );                                  \
    AIORET_TYPE (*NumberValidators)( T *self )                          \


typedef struct validator {
    VALIDATOR_INTERFACE( struct validator );
    struct validator *next;
} Validator;

#define VALIDATOR_DECLARATIONS(T)                                       \
    AIORET_TYPE ValidateChain( T*self );                                \
    void DeleteValidators( T*tmp );                                     \
    AIORET_TYPE NumberValidators( T *self );                            \
    T*NewValidator( AIORET_TYPE (*validate_fn)( T*obj ) );              \
    AIORET_TYPE AddValidator( T*self, T*next );                         \

#define VALIDATOR_MIXIN()   Validator validator;

#define MIXIN_VALIDATOR_ALLOCATOR( tmp, Validator )  memcpy( tmp, NewValidator(NULL) , sizeof(Validator))


#endif
