#include "Worker.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *Worker_toStr(Worker *self) { 
    static char buf[64];
    sprintf(buf,"%s %s", self->first,self->last );
    return buf;
}

char *Worker_firstName(Worker *self) { 
    return self->first;
}

char *Worker_lastName(Worker *self) {
    return self->last;
}

float Worker_numberYears(Worker *self) {
    return 1900+self->num_years;
}

Worker *new_Worker( char *first, char *last, int num_years ) {

    Worker *obj = (Worker *)malloc(sizeof(Worker));
    memcpy( obj, new_Employee(first,last,num_years) , sizeof(Employee));
    obj->toStr = Worker_toStr;
    BONUS_INSTANTIATION( obj );

    return obj;
}
