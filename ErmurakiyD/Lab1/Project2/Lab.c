#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main()
{
    double h, d, w1, w2 = 0;
    double plotdvp, plotdsp, plotder = 0;// 1-плотность ДВП 2-плотность ДСП 3-плотность дерева
    double m1, m2, m3, m4, m5, mvsego = 0;
    double shelves = 0; //Количество полок
    const double thic1 = 0.5;
    const double thic2 = 1.5;
    const double thic3 = 1.0;
    const double EPS = 1e-3;

    printf("Enter the height of the back wall of the cabinet:\t"); //Высота задней стенки
    scanf_s("%lf", &h);
    while (h < 180 - EPS || h > 220 + EPS) {
        printf("The value must be between 180 and 220. Enter again:\t");
        scanf_s("%lf", &h);
    }

    printf("Enter the width of the back wall of the cabinet:\t"); //Ширина задней стенки
    scanf_s("%lf", &w1);
    while (w1 < 80 - EPS || w1 > 120 + EPS) {
        printf("The value must be between 80 and 120. Enter again:\t");
        scanf_s("%lf", &w1);
    }

    printf("Enter the depth of the cabinet sidewall:\t"); //Глубина боковины
    scanf_s("%lf", &d);
    while (d < 50 - EPS || d > 90 + EPS) {
        printf("The value must be between 50 and 90. Enter again:\t");
        scanf_s("%lf", &d);
    }

   
    printf("Enter the DVP density:\t"); //Плотность ДВП
    scanf_s("%lf", &plotdvp);
    while (plotdvp < 0) {
        printf("The density cannot be negative. Enter again:\t");
        scanf_s("%lf", &plotdvp);
    }


    printf("Enter the DSP density:\t"); //Плотность ДСП
    scanf_s("%lf", &plotdsp);
    while (plotdsp < 0) {
        printf("The density cannot be negative. Enter again:\t");
        scanf_s("%lf", &plotdsp);
    }


    printf("Enter the tree density:\t"); //Плотность дерева 
    scanf_s("%lf", &plotder);
    while (plotder < 0) {
        printf("The density cannot be negative. Enter again:\t");
        scanf_s("%lf", &plotder);
    }
    

    shelves = (int)(h / (40 + thic1 * 100)); //Вычисление количества полок в шкафу
    w2 = w1 * 0.5; // Ширина двери

   
    m1 = h * w1 * thic1 * plotdvp;
    m2 = h * d * thic2 * plotdsp * 2;
    m3 = w1 * d * thic2 * plotdsp * 2;
    m4 = h * w2 * thic3 * plotder * 2;
    m5 = d * w1 * thic1 * plotdsp * shelves;
    mvsego = (m1 + m2 + m3 + m4 + m5)/1000.0;

    printf("Weight in kg:\t %lf", mvsego);
}