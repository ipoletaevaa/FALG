#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef enum {
    CONST_OK,
    CONST_ERROR
} ConstantsStatus;

ConstantsStatus e_limit(double eps, double* result);
ConstantsStatus e_series(double eps, double* result);
ConstantsStatus e_equation(double eps, double* result);

ConstantsStatus pi_limit(double eps, double* result);
ConstantsStatus pi_series(double eps, double* result);
ConstantsStatus pi_equation(double eps, double* result);

ConstantsStatus ln2_limit(double eps, double* result);
ConstantsStatus ln2_series(double eps, double* result);
ConstantsStatus ln2_equation(double eps, double* result);

ConstantsStatus sqrt2_limit(double eps, double* result);
ConstantsStatus sqrt2_product(double eps, double* result);
ConstantsStatus sqrt2_equation(double eps, double* result);

ConstantsStatus gamma_limit(double eps, double* result);
ConstantsStatus gamma_series(double eps, double* result);
ConstantsStatus gamma_equation(double eps, double* result);

#endif