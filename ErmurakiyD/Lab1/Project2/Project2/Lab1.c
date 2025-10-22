#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main() {
	double h, w1, d, w2 = 0;
	double plotdvp, plotdsp, plotder = 0;// 1-��������� ���, 2-��������� ���, 3-��������� ������
	double m1, m2, m3, m4, m5, mvsego = 0;
	int shelves = 0;// ���������� �����
	double const thic1 = 0.5; // ������� ������ ������
	double const thic2 = 1.0; // ������� �����
	double const thic3 = 1.5; // ������� �������� � ������
    double const EPS = 1e-3;

    printf("Enter the height of the back wall of the cabinet\t"); //������ ������ ������
    scanf_s("%lf", &h);
    while (h < 180 - EPS || h > 220 + EPS) {
        printf("Error, enter again:\t");
        scanf_s("%lf", &h);
    }

    printf("Enter the width of the back wall of the cabinet:\t"); //������ ������ ������
    scanf_s("%lf", &w1);
    while (w1 < 80 - EPS || w1 > 120 + EPS) {
        printf("Error, enter again:\t");
        scanf_s("%lf", &w1);
    }

    printf("Enter the depth of the sidewall cabinets:\t"); //������� ��������
    scanf_s("%lf", &d);
    while (d < 50 - EPS || d > 90 + EPS) {
        printf("Error, enter again:\t");
        scanf_s("%lf", &d);
    }
    
    
    printf("Enter the DVP density:\t"); //��������� ���
    scanf_s("%lf", &plotdvp);
    while (plotdvp < 0) {
        printf("Error, enter again:\t");
        scanf_s("%lf", &plotdvp);

    }


    printf("Enter the DSP density:\t"); //��������� ���
    scanf_s("%lf", &plotdsp);
    while (plotdsp < 0) {
        printf("Error, enter again:\t");
        scanf_s("%lf", &plotdsp);
    }


    printf("Enter the tree density:\t"); //��������� ������ 
    scanf_s("%lf", &plotder);
    while (plotder < 0) {
        printf("Error, enter again:\t");
        scanf_s("%lf", &plotder);
    }
   
    

    shelves = (int)(h / (40 + thic1 * 100));// ���������� ���������� �����
    w2 = w1 * 0.5; // ������ �����

    m1 = h * w1 * thic1 * plotdvp; 
    m2 = 2 * h * d * thic3 * plotdsp;
    m3 = 2 * w1 * d * thic3 * plotdsp;
    m4 = 2 * h * w2 * thic2 * plotder;
    m5 = d * w1 * thic1 * plotdsp * shelves;
    mvsego = (m1 + m2 + m3 + m4 + m5)/1000.0;

    printf("Weight in kg:\t %lf", mvsego);
}