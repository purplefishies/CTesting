#ifndef _VALIDATOR_H
#define _VALIDATOR_H

typedef int AIORET_TYPE;

typedef struct validator {
    AIORET_TYPE (*Validate)( struct validator *obj );
    AIORET_TYPE (*ValidateChain)( struct validator *obj );
    AIORET_TYPE (*AddValidator)( struct validator *self, struct validator *next );
    AIORET_TYPE (*DeleteValidators)( struct validator *top );
    AIORET_TYPE (*NumberValidators)( struct validator  *self );
    struct validator *next;
} Validator;


#endif
