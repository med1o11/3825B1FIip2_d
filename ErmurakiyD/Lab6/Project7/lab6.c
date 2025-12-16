#define _CRT_SECURE_NO_WARNINGS
#define pi 3.14159265358979323846L  
#include <stdio.h>
#include <math.h>

long double reduce_angle(long double x) {
    x = fmodl(x, 2.0L * pi);

    if (x > pi) {
        x -= 2.0L * pi;
    }
    else if (x < -pi) {
        x += 2.0L * pi;
    }

    return x;
}

long double lf_sin(long double eps, size_t n, long double x, size_t* i_count) {
    long double res = 0;
    long double reduced_x = reduce_angle(x);
    long double term = reduced_x;
    long double x_squared = reduced_x * reduced_x;
    short int sign = 1;
    *i_count = 0;

    for (size_t i = 0; i < n; ++i) {
        res += sign * term;
        (*i_count)++;
        if (fabsl(term) < eps) {
            break;
        }
        term = term * x_squared / ((2.0L * i + 2.0L) * (2.0L * i + 3.0L));
        sign *= -1;
    }
    return res;
}

long double lf_cos(long double eps, size_t n, long double x, size_t* i_count) {
    long double res = 0;
    long double reduced_x = reduce_angle(x);
    long double term = 1.0L;
    long double x_squared = reduced_x * reduced_x;
    short int sign = 1;
    *i_count = 0;

    for (size_t i = 0; i < n; ++i) {
        res += sign * term;
        (*i_count)++;
        if (fabsl(term) < eps) {
            break;
        }
        term = term * x_squared / ((2.0L * i + 1.0L) * (2.0L * i + 2.0L));
        sign *= -1;
    }
    return res;
}

long double lf_exp(long double eps, size_t n, long double x, size_t* i_count) {
    long double res = 0;
    long double term = 1;
    *i_count = 0;
    for (size_t i = 0; i < n; ++i) {
        res += term;
        (*i_count)++;
        if (fabsl(term) < eps) {
            break;
        }
        term /= (i + 1);
        term *= x;
    }
    return res;
}

long double lf_arctg(long double eps, size_t n, long double x, size_t* i_count) {
    if (fabsl(x) > 1) {
        long double sign = (x > 0) ? 1.0L : -1.0L;
        x = 1.0L / x;
        long double res = lf_arctg(eps, n, x, i_count);
        return sign * (pi / 2.0L - res);
    }

    long double res = 0;
    long double term = x;
    long double x_squared = x * x;
    short int sign = 1;
    *i_count = 0;

    for (size_t i = 0; i < n; ++i) {
        res += sign * term;
        (*i_count)++;
        if (fabsl(term) < eps) {
            break;
        }
        term *= x_squared;
        sign *= -1;
        term /= (2 * i + 3);
    }
    return res;
}

long double (*lf_func(int choice))(long double, size_t, long double, size_t*) {
    switch (choice) {
    case 1:
        return lf_sin;
        break;
    case 2:
        return lf_cos;
        break;
    case 3:
        return lf_exp;
        break;
    case 4:
        return lf_arctg;
        break;
    default:
        return NULL;
    }
}

long double (*standard_func(int choice))(long double) {
    switch (choice) {
    case 1:
        return sinl;
        break;
    case 2:
        return cosl;
        break;
    case 3:
        return expl;
        break;
    case 4:
        return atanl;
        break;
    default:
        return NULL;
    }
}

int select_mode() {
    printf("Select the program mode:\n1 - Singular calculation.\n2 - Serial calculation.\n");
    int choice;
    while (scanf("%d", &choice) != 1 || choice > 2 || choice < 1) {
        printf("Incorrect input. Please try again.\n");
        char c;
        while ((c = getchar()) != '\n') {}
    }
    return choice;
}

int select_function() {
    printf("Select function:\n1 - Sin.\n2 - Cos.\n3 - Exp.\n4 - Arctg.\n");
    int choice;
    while (scanf("%d", &choice) != 1 || choice > 4 || choice < 1) {
        printf("Incorrect input. Please try again.\n");
        while (getchar() != '\n');
    }
    return choice;
}

int main() {
    int mode = select_mode();
    int choice = select_function();
    size_t i = 0;
    size_t* i_count = &i;

    long double(*fnc)(long double) = standard_func(choice);
    long double(*lf_fnc)(long double, size_t, long double, size_t*) = lf_func(choice);

    if (fnc == NULL || lf_fnc == NULL) {
        printf("Error: Invalid function selection.\n");
        return 1;
    }

    switch (mode) {
    case 1: {
        printf("Input x.\n");
        long double x;
        while (scanf("%Lf", &x) != 1) {
            printf("Incorrect input. Please try again.\n");
            char c;
            while ((c = getchar()) != '\n') {}
        }

        printf("Input EPS.(mustn't be less than 1e-6)\n");
        long double eps;
        while (scanf("%Lf", &eps) != 1 || eps < 1e-6) {
            printf("Incorrect input. Please try again.\n");
            char c;
            while ((c = getchar()) != '\n') {}
        }

        printf("Input n.(must be integer in [1;1000])\n");
        size_t n;
        while (scanf("%zu", &n) != 1 || n < 1 || n > 1000) {
            printf("Incorrect input. Please try again.\n");
            char c;
            while ((c = getchar()) != '\n') {}
        }

        long double my_result = lf_fnc(eps, n, x, i_count);
        long double std_result = fnc(x);

        printf("Math.h function: %Lf\n", std_result);
        printf("My function: %Lf\n", my_result);
        printf("Difference: %Le\n", fabsl(my_result - std_result));
        printf("Deg. of Taylor series: %zu\n", *i_count);
        break;
    }

    case 2: {
        printf("Input x.\n");
        long double x;
        while (scanf("%Lf", &x) != 1) {
            printf("Incorrect input. Please try again.\n");
            char c;
            while ((c = getchar()) != '\n') {}
        }

        printf("Input nmax.(must be integer in [1;25])\n");
        size_t nmax;
        while (scanf("%zu", &nmax) != 1 || nmax < 1 || nmax > 25) {
            printf("Incorrect input. Please try again.\n");
            char c;
            while ((c = getchar()) != '\n') {}
        }

        long double std_result = fnc(x);
        printf("Math.h function: %Lf\n\n", std_result);

        for (size_t n = 1; n < nmax + 1; ++n) {
            long double my_result = lf_fnc(0.0L, n, x, i_count);
            printf("Deg. of Taylor series: %zu\tMy function: %Lf\tDifference: %Le\n",
                n, my_result, fabsl(my_result - std_result));
        }
        break;
    }
    }

    return 0;
}