#include "Bonus.h"
#include "Employee.h"

float bonus( void *obj , float refval ) {
    Employee *emp = (Employee*)obj;
    return (1+emp->numberYears(emp)) * refval;
}
