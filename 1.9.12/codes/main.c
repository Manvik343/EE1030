#include <stdio.h>
double distance(double, double, double, double);
void midpoint(double, double, double, double);
int main(){
	printf("distance=%lf\n",distance(-6, 7, -1, -5));
	midpoint(-6, 7, -1, -5);
	return 0;
}
