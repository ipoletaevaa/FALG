#include <stdio.h>
#include "../include/constants.h"

int main() {
    double eps = 1e-5;
    double result;
    
    printf("Вычисление математических констант с точностью %.0e\n\n", eps);
    
    printf("e:\n");
    e_limit(eps, &result); printf("  Предел:    %.10f\n", result);
    e_series(eps, &result); printf("  Ряд:       %.10f\n", result);
    e_equation(eps, &result); printf("  Уравнение: %.10f\n", result);
    printf("  Эталон:    2.7182818284\n\n");
    
    printf("Число П:\n");
    pi_limit(eps, &result); printf("  Предел:    %.10f\n", result);
    pi_series(eps, &result); printf("  Ряд:       %.10f\n", result);
    pi_equation(eps, &result); printf("  Уравнение: %.10f\n", result);
    printf("  Эталон:    3.1415926535\n\n");
    
    printf("ln(2):\n");
    ln2_limit(eps, &result); printf("  Предел:    %.10f\n", result);
    ln2_series(eps, &result); printf("  Ряд:       %.10f\n", result);
    ln2_equation(eps, &result); printf("  Уравнение: %.10f\n", result);
    printf("  Эталон:    0.6931471805\n\n");
    
    printf("√2:\n");
    sqrt2_limit(eps, &result); printf("  Предел:    %.10f\n", result);
    sqrt2_product(eps, &result); printf("  Произв.:   %.10f\n", result);
    sqrt2_equation(eps, &result); printf("  Уравнение: %.10f\n", result);
    printf("  Эталон:    1.4142135623\n\n");
    
    printf("постоянная Эйлера:\n");
    gamma_limit(eps, &result); printf("  Предел:    %.10f\n", result);
    gamma_series(eps, &result); printf("  Ряд:       %.10f\n", result);
    gamma_equation(eps, &result); printf("  Уравнение: %.10f\n", result);
    printf("  Эталон:    0.5772156649\n");
    
    return 0;
}