#include "Employee.h"
#include <stdlib.h>
#include <string.h>

char *firstName(Employee *self) 
{
    return self->first;
}

char *lastName(Employee *self) { 
    return self->last;
}

int numberYears(Employee *self) { 
    return self->num_years + 1900;
}

Employee *new_Employee( char *first, char *last, int num_years) 
{
    Employee *obj = (Employee *)malloc(sizeof(Employee));
    if( !obj ) 
        return NULL;
    obj->first        = strdup(first);
    obj->last         = strdup(last);
    obj->num_years    = num_years;
    obj->firstName    = firstName;
    obj->lastName     = lastName;
    obj->numberYears  = numberYears;
    return obj;
}

