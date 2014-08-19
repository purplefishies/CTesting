#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gtest/gtest.h"
#include "tap.h"
#include "validator.h"

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

class ValidateSetup : public ::testing::Test 
{
 protected:
    virtual void SetUp() {
        curvalue = 0;
        memset(buf,0,BUFSIZE );
        top = NULL;
        /* int BUFSIZE = 1024; */
        /* buf = (char *)malloc(BUFSIZE); */
    }
  
    virtual void TearDown() { 
    }
 public:
    static const int BUFSIZE = 1024;
    static char buf[BUFSIZE];
    static int curvalue;
    Validator *top;
};

int ValidateSetup::curvalue;
char ValidateSetup::buf[BUFSIZE];

AIORET_TYPE check_test( Validator *obj )
{
    sprintf( ValidateSetup::buf,"%s%d", ValidateSetup::buf, ValidateSetup::curvalue );
    ValidateSetup::curvalue += 1;
}

AIORET_TYPE fails_on_the_last( Validator *obj )
{
    if ( ValidateSetup::curvalue++ >= 100 ) { 
        return -1;
    } else {
        return 0;
    }
}

TEST_F(ValidateSetup,CoreValidate )
{
    /* Validator *top = NULL; */
    Validator *ttmp = NewValidator( check_test );
    AIORET_TYPE retval;
    /* memset(buf,0, BUFSIZE ); */
    /* curvalue = 0; */
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

TEST_F(ValidateSetup, ShouldFailValidate )
{
    /* Validator *top = NULL; */
    Validator *ttmp = NewValidator( check_test );
    AIORET_TYPE retval;
    /* AIORET_TYPE retval; */
    /* memset(buf,0, BUFSIZE ); */
    /* curvalue = 0; */
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
