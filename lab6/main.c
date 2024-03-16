#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EXIT_SUCCESS 0
#define A 1
#define B 3
#define E 0.012

void  method_golden_section();
void  method_polyline();
void  method_tangent();
void  method_Newton();
double f(double x);

int main(void) {
    method_golden_section();
    method_polyline();
    method_tangent();
    method_Newton();
    return EXIT_SUCCESS;
}

double f(double x){
    return exp(1/x)+log(x);
}

double f1(double x){
    return 1/x-exp(1/x)/pow(x,2);
}

double f2(double x){
    return ((2*x+1)*exp(1/x))/pow(x,4)-1/pow(x,2);
}

void  method_golden_section(){
    const double golden_ratio = (1 + sqrt(5)) / 2;
	double x1, x2, a=A, b=B; 
	while (fabs(b - a) > E) {
		   x1 = b - (b - a) / golden_ratio; 
	       x2 = a + (b - a) / golden_ratio;
	       if (f(x1) >= f(x2)) 
	           a = x1; 
	       else 
	           b = x2;
	}
    FILE *output;
    output= fopen("output.txt", "a+");
    fprintf(output,"method golden section\n%f\n", f((a+b)/2));
    fclose(output);
}

double delta(double x, double p, double L){
    return 1/(2*L)*(f(x)-p);
}

void  method_polyline(){
    double tmpL, L = 0;
	double h = fabs(B - A)/10000;
	for(double i = A + h; i <= B; i += h){
		tmpL = fabs( f(i) - f(i - h) ) / h;
		if(tmpL > L)
            L = tmpL;
    } 
    double x=1/(2*L)*(f(A)-f(B)+L*(A+B)), p=(f(A)+f(B)+L*(A-B))/2;
    double x1[2]={x-delta(x,p,L), x+delta(x,p,L)};
    double p1=(f(x1[0])+p)/2;
    double x_min=(f(x1[0])<f(x1[1]))?x1[0]:x1[1];
    while(fabs(f(x)-f(x_min))>E){
        x=x_min;
        p=p1;
        x1[0]=x-delta(x,p,L),x1[1]=x+delta(x,p,L);
        p1=1/2*(f(x1[0])-p);
        x_min=(f(x1[0])<f(x1[1]))?x1[0]:x1[1];
    }
    FILE *output;
    output= fopen("output.txt", "a+");
    fprintf(output,"method polyline\n%f\n", f(x_min));
    fclose(output);
}

void  method_tangent(){
    double a=A, b=B;
    double c = (b*f1(b)-a*f1(a)+f(a)-f(b))/(f1(b)-f1(a));
    if (f1(c)>=0)
        a=a , b=c;
    else
        a=c, b=b;
    while(fabs(f1(c))>E){
        c = (b*f1(b)-a*f1(a)+f(a)-f(b))/(f1(b)-f1(a));
        if (f1(c)>=0)
            a=a , b=c;
        else
            a=c, b=b;
    }
    FILE *output;
    output= fopen("output.txt", "a+");
    fprintf(output,"method tangent\n%f\n", f(c));
    fclose(output);
}

void  method_Newton(){
    double x0=(A+B)/2;
    double x = x0 - f1(x0)/f2(x0), xn;
    while (fabs(f1(x))>E){
        xn=x-f1(x)/f2(x);
        x=xn;
    }
    FILE *output;
    output= fopen("output.txt", "a+");
    fprintf(output,"method Newton\n%f\n", f(x));
    fclose(output);
}