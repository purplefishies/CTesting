#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Employee.h"
#include "Bonus.h"


typedef struct _Worker Worker;

#define WORKER_INTERFACE                       \
    EMPLOYEE_INTERFACE( Worker );              \
    char *(*toStr)(Worker *self);

typedef struct _Worker { 
    WORKER_INTERFACE;
    BONUS_MIXIN( Worker );
} Worker;

Worker *new_Worker(char *first, char *last, int num_years );



#endif
