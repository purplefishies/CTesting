#include <stdio.h>


typedef struct {
    int a;
    char *b;
    double c;
} Datum;

char *DatumToStr( Datum *d ) {
    static char buf[256];
    sprintf(buf,"a:%d,b:%s,c:%f",d->a,d->b,d->c);
    return buf;
}

#define DATUM_PTR(a,b,c) ({Datum tmp = {a,b,c}; &tmp;})

int main(int argc, char *argv ) {

    Datum blah = {0};
    
    printf("Data is %s\n", DatumToStr(&blah) );
    /* DatumToStr( ({Datum tmp = {4,0,3.344} ; &blah}) ); */
    /* Datum *ptr = ({Datum tmp = {4,0,3.344};&tmp;}); */
    /* printf("Data is %s\n", DatumToStr(ptr) ); */
    /* printf("Other data is %s\n",DatumToStr( ({Datum tmp = {4,0,3.344};&tmp;}) )); */  
    printf("Other data is %s\n",DatumToStr( DATUM_PTR(4,"foo",3.344) ));


}











