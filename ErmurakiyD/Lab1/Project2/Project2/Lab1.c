#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main() {
	double h, w1, d, w2 = 0;
	double plotdvp, plotdsp, plotder = 0;// 1-плотность двп, 2-плотность дсп, 3-плотность дерева
	double m1, m2, m3, m4, m5, mvsego = 0;
	int shelves = 0;// количество полок
	double const thic1 = 0.5; // толщина задней стенки
	double const thic2 = 1.0; // толщина двери
	double const thic3 = 1.5; // толщина боковины и крышек
    double const EPS = 1e-3;

    printf("Enter the height of the back wall of the cabinet\t"); //Высота задней стенки
    scanf_s("%lf", &h);
    while (h < 180 - EPS || h > 220 + EPS) {
        printf("Error, enter again:\t");
        scanf_s("%lf", &h);
    }

    printf("Enter the width of the back wall of the cabinet:\t"); //Ширина задней стенки
    scanf_s("%lf", &w1);
    while (w1 < 80 - EPS || w1 > 120 + EPS) {
        printf("Error, enter again:\t");
        scanf_s("%lf", &w1);
    }

    printf("Enter the depth of the sidewall cabinets:\t"); //Глубина боковины
    scanf_s("%lf", &d);
    while (d < 50 - EPS || d > 90 + EPS) {
        printf("Error, enter again:\t");
        scanf_s("%lf", &d);
    }
    
    
    printf("Enter the DVP density:\t"); //Плотность ДВП
    scanf_s("%lf", &plotdvp);
    while (plotdvp < 0) {
        printf("Error, enter again:\t");
        scanf_s("%lf", &plotdvp);

    }


    printf("Enter the DSP density:\t"); //Плотность ДСП
    scanf_s("%lf", &plotdsp);
    while (plotdsp < 0) {
        printf("Error, enter again:\t");
        scanf_s("%lf", &plotdsp);
    }


    printf("Enter the tree density:\t"); //Плотность дерева 
    scanf_s("%lf", &plotder);
    while (plotder < 0) {
        printf("Error, enter again:\t");
        scanf_s("%lf", &plotder);
    }
   
    

    shelves = (int)(h / (40 + thic1 * 100));// Вычисление количества колок
    w2 = w1 * 0.5; // Ширина двери

    m1 = h * w1 * thic1 * plotdvp; 
    m2 = 2 * h * d * thic3 * plotdsp;
    m3 = 2 * w1 * d * thic3 * plotdsp;
    m4 = 2 * h * w2 * thic2 * plotder;
    m5 = d * w1 * thic1 * plotdsp * shelves;
    mvsego = (m1 + m2 + m3 + m4 + m5)/1000.0;

    printf("Weight in kg:\t %lf", mvsego);
}