#include <math.h>
#include <stddef.h>
#include <float.h>
#include <limits.h>
#include "constants.h"

static double harmonic_number(int n) {
    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        sum += 1.0 / i;
    }
    return sum;
}

ConstantsStatus gamma_limit(double eps, double* result) {
    if (eps <= 0 || result == NULL) return CONST_ERROR;
    
    double current = 0.0;
    double prev;
    int n = 1;
    const int max_iterations = 1000000;
    
    do {
        prev = current;
        double H_n = harmonic_number(n);
        current = H_n - log(n) - 1.0/(2.0*n) + 1.0/(12.0*n*n);
        n *= 2;
        
    } while (n < max_iterations && fabs(current - prev) > eps);
    
    *result = current;
    return CONST_OK;
}

ConstantsStatus gamma_series(double eps, double* result) {
    if (eps <= 0 || result == NULL) return CONST_ERROR;
    
    double sum = 0.0;
    int n = 1;
    double term;
    const int max_iterations = 1000000;
    
    do {
        term = 1.0/n - log(1.0 + 1.0/n);
        sum += term;
        n++;
        
    } while (n < max_iterations && fabs(term) > eps);
    
    *result = sum;
    return CONST_OK;
}

ConstantsStatus gamma_equation(double eps, double* result) {
    if (eps <= 0 || result == NULL) return CONST_ERROR;
    
    double n = 1000000.0;
    double H_n = 0.0;
    
    for (int i = 1; i <= (int)n; i++) {
        H_n += 1.0 / i;
    }
    
    double gamma_approx = H_n - log(n);
    gamma_approx -= 1.0/(2.0*n) - 1.0/(12.0*n*n) + 1.0/(120.0*n*n*n*n);
    
    *result = gamma_approx;
    return CONST_OK;
}

ConstantsStatus e_limit(double eps, double* result) {
    if (eps <= 0 || result == NULL) return CONST_ERROR;
    
    long long n = 1;
    double current = 2.0;
    double prev;
    
    do {
        prev = current;
        n *= 2;
        current = pow(1.0 + 1.0 / n, n);
    } while (n < LLONG_MAX / 2 && fabs(current - prev) > eps);
    
    *result = current;
    return CONST_OK;
}

ConstantsStatus e_series(double eps, double* result) {
    if (eps <= 0 || result == NULL) return CONST_ERROR;
    
    double sum = 1.0;
    double term = 1.0;
    int n = 1;
    
    do {
        term /= n;
        sum += term;
        n++;
    } while (fabs(term) > eps && n < 1000000);
    
    *result = sum;
    return CONST_OK;
}

ConstantsStatus e_equation(double eps, double* result) {
    if (eps <= 0 || result == NULL) return CONST_ERROR;
    
    double x = 2.0;
    double prev;
    
    do {
        prev = x;
        x = prev - (log(prev) - 1.0) / (1.0 / prev);
    } while (fabs(x - prev) > eps);
    
    *result = x;
    return CONST_OK;
}

ConstantsStatus pi_limit(double eps, double* result) {
    if (eps <= 0 || result == NULL) return CONST_ERROR;
    
    double product = 1.0;
    int n = 1;
    double prev_value = 0.0;
    double current_value = 2.0;
    
    const int max_iterations = 1000000;
    
    do {
        prev_value = current_value;
        product *= (4.0 * n * n) / (4.0 * n * n - 1.0);
        current_value = 2.0 * product;
        n++;
    } while (n < max_iterations && fabs(current_value - prev_value) > eps);
    
    *result = current_value;
    return CONST_OK;
}

ConstantsStatus pi_series(double eps, double* result) {
    if (eps <= 0 || result == NULL) return CONST_ERROR;
    
    double sum = 0.0;
    int n = 0;
    double term;
    
    do {
        term = (n % 2 == 0 ? 1.0 : -1.0) / (2 * n + 1);
        sum += term;
        n++;
    } while (fabs(term) > eps && n < 1000000);
    
    *result = 4 * sum;
    return CONST_OK;
}

ConstantsStatus pi_equation(double eps, double* result) {
    if (eps <= 0 || result == NULL) return CONST_ERROR;
    
    double x = 3.0;
    double prev;
    int iterations = 0;
    const int max_iterations = 1000;
    
    do {
        prev = x;
        x = prev - sin(prev) / cos(prev);
        iterations++;
    } while (iterations < max_iterations && fabs(x - prev) > eps);
    
    *result = x;
    return CONST_OK;
}

ConstantsStatus ln2_limit(double eps, double* result) {
    if (eps <= 0 || result == NULL) return CONST_ERROR;
    
    double current = 0.0;
    double prev = 0.0;
    int n = 1;
    
    do {
        prev = current;
        current = n * (pow(2, 1.0 / n) - 1);
        n++;
    } while (n < 1000000 && fabs(current - prev) > eps);
    
    *result = current;
    return CONST_OK;
}

ConstantsStatus ln2_series(double eps, double* result) {
    if (eps <= 0 || result == NULL) return CONST_ERROR;
    
    double sum = 0.0;
    int n = 1;
    double term;
    
    do {
        term = (n % 2 == 0 ? -1.0 : 1.0) / n;
        sum += term;
        n++;
    } while (fabs(term) > eps && n < 1000000);
    
    *result = sum;
    return CONST_OK;
}

ConstantsStatus ln2_equation(double eps, double* result) {
    if (eps <= 0 || result == NULL) return CONST_ERROR;
    
    double x = 0.7;
    double prev;
    
    do {
        prev = x;
        x = prev - (exp(prev) - 2.0) / exp(prev);
    } while (fabs(x - prev) > eps);
    
    *result = x;
    return CONST_OK;
}

ConstantsStatus sqrt2_limit(double eps, double* result) {
    if (eps <= 0 || result == NULL) return CONST_ERROR;
    
    double x = -0.5;
    double prev;
    
    do {
        prev = x;
        x = prev - (prev * prev) / 2.0 + 1.0;
    } while (fabs(x - prev) > eps);
    
    *result = x;
    return CONST_OK;
}

ConstantsStatus sqrt2_product(double eps, double* result) {
    if (eps <= 0 || result == NULL) return CONST_ERROR;
    
    double product = 1.0;
    int k = 2;
    double factor, prev_product;
    
    do {
        prev_product = product;
        factor = pow(2, pow(2, -k));
        product *= factor;
        k++;
    } while (k < 1000 && fabs(product - prev_product) > eps);
    
    *result = product;
    return CONST_OK;
}

ConstantsStatus sqrt2_equation(double eps, double* result) {
    if (eps <= 0 || result == NULL) return CONST_ERROR;
    
    double x = 1.5;
    double prev;
    
    do {
        prev = x;
        x = prev - (prev * prev - 2.0) / (2 * prev);
    } while (fabs(x - prev) > eps);
    
    *result = x;
    return CONST_OK;
}