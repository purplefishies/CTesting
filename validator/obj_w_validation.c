#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "validator.h"

typedef struct object_that_needs_validation {
    VALIDATOR_INTERFACE( struct object_that_needs_validation ); /* All the function defs */
    VALIDATOR_MIXIN();                                          /* the actual validator object */
    int x;
    char *y;
} ObjectWithValidation;

VALIDATOR_DECLARATIONS( Validator );


/*----------------------------------------------------------------------------*/
ObjectWithValidation *NewObjectWithValidation( int xx, const char *yy )
{
    ObjectWithValidation *tmp = (ObjectWithValidation*)calloc(sizeof(ObjectWithValidation),1);
    MIXIN_VALIDATOR_ALLOCATOR( tmp, Validator );

    if ( !tmp ) 
        return tmp;
    tmp->x = xx;
    tmp->y = strdup(yy);
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
    /* printf("Here !\n"); */
    if ( strlen(obj->y) <= 23 ) {
        return 0;
    } else {
        /* printf("Result: %d\n", (int)strlen(obj->y)); */
        return -1;
    }
}

#ifdef SELF_TEST

#include "gtest/gtest.h"
#include "tap.h"

TEST(ObjectWithValidation,BasicSetup )
{
    ObjectWithValidation *top = NewObjectWithValidation( 3, "A string" );
    AIORET_TYPE result ;
    top->AddValidator( top,  NewValidator( (VALIDATOR_FN)check_x_value ) );
    top->AddValidator( top,  NewValidator( (VALIDATOR_FN)check_str_value ) );
    EXPECT_EQ( 2, top->NumberValidators( top ) );

    result = top->ValidateChain( top );
    EXPECT_EQ( result , SUCCESS );
}

TEST(ObjectWithValidation,ShouldFailValidate )
{
    ObjectWithValidation *top = NewObjectWithValidation( 244, "A string" );
    AIORET_TYPE result ;

    top->AddValidator( top,  NewValidator( (int (*)(validator*))check_x_value ) );
    top->AddValidator( top,  NewValidator( (int (*)(validator*))check_str_value ) );
    result = top->ValidateChain( top );
    EXPECT_LE( result , SUCCESS );
    top->DeleteValidators( top );

    top = NewObjectWithValidation( 24, "A very very very very very very very very long string" );
    top->AddValidator( top,  NewValidator( (int (*)(validator*))check_x_value ) );
    top->AddValidator( top,  NewValidator( (int (*)(validator*))check_str_value ) );
    result = top->ValidateChain( top );
    EXPECT_LE( result, SUCCESS );

    top->DeleteValidators( top );
    top = NewObjectWithValidation( 24, "Exactly 22 characters" );
    top->AddValidator( top,  NewValidator( (int (*)(validator*))check_x_value ) );
    top->AddValidator( top,  NewValidator( (int (*)(validator*))check_str_value ) );
    result = top->ValidateChain( top );
    EXPECT_EQ( result, SUCCESS );

}


int
main(int argc, char *argv[] ) 
{
    testing::InitGoogleTest(&argc, argv);
    testing::TestEventListeners & listeners = testing::UnitTest::GetInstance()->listeners();
#ifdef GTEST_TAP_PRINT_TO_STDOUT
    delete listeners.Release(listeners.default_result_printer());
#endif
    /* listeners.Append( new tap::TapListener() ); */
   
    return RUN_ALL_TESTS();  
}

#endif
