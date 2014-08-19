#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gtest/gtest.h"
#include "tap.h"

typedef int AIORET_TYPE;

typedef struct validator {
    AIORET_TYPE (*Validate)( struct validator *obj );
    AIORET_TYPE (*ValidateChain)( struct validator *obj );
    AIORET_TYPE (*AddValidator)( struct validator *self, struct validator *next );
    AIORET_TYPE (*DeleteValidators)( struct validator *top );
    AIORET_TYPE (*NumberValidators)( struct validator  *self );
    struct validator *next;
} Validator;

/*----------------------------------------------------------------------------*/
AIORET_TYPE ValidateChain( Validator *self ) 
{
    AIORET_TYPE result = 0;
    for ( Validator *cur = self; cur && cur->next ; cur = cur->next ) {
        if ( cur->Validate ) {
            AIORET_TYPE tmpresult = cur->Validate( cur );
            result |= tmpresult;
            if ( result < 0 ) 
                break;
        }
    }
    return result;
}

/*----------------------------------------------------------------------------*/
void DeleteValidators( Validator *tmp ) 
{
    Validator *cur = tmp;
    Validator *next = NULL;
    for( cur = tmp; cur; cur = next ) {
        if ( !cur )
            break;
        next = cur->next;
        free(cur);
    }
}

/*----------------------------------------------------------------------------*/
AIORET_TYPE NumberValidators( Validator  *self )
{
    if ( !self ) { 
        return -1;
    }
    int count = 0;
    Validator *cur;
    for (cur = self; cur->Validate && cur->next ; cur = cur->next, count ++ );

    if ( count == 0 && cur->Validate ) 
        count ++;

    return count;
}

/*----------------------------------------------------------------------------*/
Validator *NewValidator( AIORET_TYPE (*validate_fn)( Validator *obj ) ) 
{
    Validator *tmp = (Validator*)calloc(sizeof(Validator),1);
    if ( !tmp ) 
        return tmp;
    /* tmp->parent = parent; */
    tmp->Validate = validate_fn;
    tmp->ValidateChain = ValidateChain;
    tmp->NumberValidators = NumberValidators;
    return tmp;
}

/*----------------------------------------------------------------------------*/
AIORET_TYPE AddValidator( Validator **self, Validator *next )
{
    AIORET_TYPE result = 0;
    if ( !next ) 
        return -1;
    if ( !*self )  {
        *self = next;
        return result;
    }
    Validator *cur;
    for ( cur = (*self); cur->Validate && cur->next ; cur = cur->next );

    if ( !cur ) {
        *self = cur;
    } else {
        cur->next = next;
    }

    return result;
}

typedef struct object_that_needs_validation {
    int x;
    char *y;
} ObjectWithValidation;

/*----------------------------------------------------------------------------*/
ObjectWithValidation *NewObjectWithValidation( int xx, const char *yy )
{
    ObjectWithValidation *tmp = (ObjectWithValidation*)calloc(sizeof(ObjectWithValidation),1);
    if ( !tmp ) 
        return tmp;
    tmp->x = xx;
    tmp->y = strdup(yy);
    /* tmp->validator = NULL; */
}

/*----------------------------------------------------------------------------*/
AIORET_TYPE ObjectWithValidationAddValidator( ObjectWithValidation **self, Validator *validator )
{
    /* AddValidator( self, validator ); */
    printf("something\n");
}

/*----------------------------------------------------------------------------*/
AIORET_TYPE check_x_value( ObjectWithValidation *obj )
{
    if ( obj->x < 25 ) { 
        return 0;
    } else {
        return -1;
    }
}

AIORET_TYPE check_str_value( ObjectWithValidation *obj )
{
    if ( strlen(obj->y) < 15 ) {
        return 0;
    } else {
        return -1;
    }
}

int BUFSIZE = 1024;
char buf[1024];
int curvalue;

AIORET_TYPE check_test( Validator *obj )
{
    sprintf(buf,"%s%d",buf, curvalue );
    curvalue += 1;
}

AIORET_TYPE fails_on_the_last( Validator *obj )
{
    if ( curvalue++ >= 100 ) { 
        return -1;
    } else {
        return 0;
    }
}




TEST(Validate,CoreValidate )
{
    Validator *top = NULL;
    Validator *ttmp = NewValidator( check_test );
    AIORET_TYPE retval;
    memset(buf,0, BUFSIZE );
    curvalue = 0;
    AddValidator( &top, ttmp );
    for ( int i = 0; i < 100 ; i ++ ) { 
        AddValidator( &top, NewValidator( check_test ));
    } 
    retval = top->ValidateChain( top );
    EXPECT_STREQ("0123456789101112131415161718192021222324252627282930313233343536373839404142434445464748495051525354555657585960616263646566676869707172737475767778798081828384858687888990919293949596979899", buf );
    EXPECT_GE( retval, 0 );
    EXPECT_EQ(top->NumberValidators(top), 100 );

    DeleteValidators( top );
}

TEST(Validate, ShouldFailValidate )
{
    Validator *top = NULL;
    Validator *ttmp = NewValidator( check_test );
    AIORET_TYPE retval;
    memset(buf,0, BUFSIZE );
    curvalue = 0;
    AddValidator( &top, ttmp );
    for ( int i = 0; i < 101; i ++ ) { 
        AddValidator( &top, NewValidator( fails_on_the_last ));
    }
    EXPECT_EQ(top->NumberValidators(top), 101 );
    retval = top->ValidateChain( top );
    EXPECT_LE( retval, 0 );
    DeleteValidators( top );

}

int
main(int argc, char *argv[] ) 
{
    testing::InitGoogleTest(&argc, argv);
    testing::TestEventListeners & listeners = testing::UnitTest::GetInstance()->listeners();
#ifdef GTEST_TAP_PRINT_TO_STDOUT
    delete listeners.Release(listeners.default_result_printer());
#endif
    listeners.Append( new tap::TapListener() );
   
    return RUN_ALL_TESTS();  
}
