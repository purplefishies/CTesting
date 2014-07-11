#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Bonus.h"

typedef struct _Employee Employee;


#define EMPLOYEE_API_INTERFACE( T ) char *(*firstName)(T *);     \
    char * (*lastName)(T *);                                     \
    int (*numberYears)(T *);                                     \
    char *first;                                                 \
    char *last;                                                  \
    int num_years;

#define EMPLOYEE_INTERFACE( T ) \
    EMPLOYEE_API_INTERFACE( T )

typedef struct _Employee {
    EMPLOYEE_API_INTERFACE(Employee);
    BONUS_MIXIN( Employee );
} Employee;

Employee *new_Employee(char *first, char *last, int year_joined_since_1900 );


#endif
