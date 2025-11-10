#include <stdio.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
void main() {
	double x, y, r, x1, y1, r1;
	printf("Enter the coordinates of circle 1\n");
	scanf_s("%lf%lf", &x, &y);

	printf("Enter the radius of circle 1\n");
	scanf_s("%lf", &r);

	printf("Enter the coordinates of circle 2\n");
	scanf_s("%lf%lf", &x1, &y1);

	printf("Enter the radius of circle 2\n");
	scanf_s("%lf", &r1);

	if (r <= 0 || r1 <= 0) {
		printf("The radius should not be negative or zero\n");
		return 1;
	}

	double s = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));

	if ((r + r1 < s) || (fabs(r - r1) > s)) {
		printf("the circles don't touch and don't intersect\n");
	}
	else if ((fabs(r - r1) == s) || (r + r1 == s)) {
		printf("the circles touch each other\n");
	}
	else {
		printf("the circles intersect with each other");
	}
	return 0;
}