#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EXIT_SUCCESS 0
#define E 0.0001
#define A 2
#define B 12

void method_euler(double);
void method_euler_mod(double);
void method_euler_improve(double);
void method_runge_kutt(double);
void print_n(double);
double f (double, double);
double f1 (double, double);

int main(void) {
    double h, step[3] = {0.5, 0.1, 0.01};
    for(int i = 0; i < 3; i++) {
        h = step[i];
        print_n(h);
        method_euler(h);
        method_euler_mod(h);
        method_euler_improve(h);
        method_runge_kutt(h);
    }
    return EXIT_SUCCESS;
}

void method_euler(double h) {
    FILE *output;
    output = fopen("output.txt", "a+");
    fprintf(output,"\n%6s", "y_e =");

    double n=(B-A)/h;
    double X[(int)n], Y[(int)n];
    X[0]=A; Y[0]=5;
    fprintf(output, "%f ", Y[0]);
    for(int i=1; i<=n; i++){
        X[i]=A+i*h;
        Y[i]=Y[i-1]+h*f(X[i-1],Y[i-1]);
        fprintf(output, "%f ", Y[i]);
    }
    fclose(output);
}

void method_euler_mod(double h) {
    FILE *output;
    output = fopen("output.txt", "a+");
    fprintf(output,"\n%6s", "y_em =");

    double n=(B-A)/h;
    double X[(int)n], Y[(int)n];
    X[0]=A; Y[0]=5;
    fprintf(output, "%f ", Y[0]);
    for(int i=1; i<=n; i++){
        int x = X[i-1]+h/2;
        int y = Y[i-1]+h/2*f1(X[i-1],Y[i-1]);
        Y[i]= Y[i-1]+h*f(x,y);
        X[i]=X[i-1]+h;
        fprintf(output, "%f ", Y[i]);
    }
    fclose(output);
}

void method_euler_improve(double h) {
    FILE *output;
    output = fopen("output.txt", "a+");
    fprintf(output,"\n%6s", "y_ei =");

    double n=(B-A)/h;
    double X[(int)n], Y[(int)n];
    X[0]=A; Y[0]=5;
    fprintf(output, "%f ", Y[0]);
    for(int i=1; i<=n; i++){
        int y = Y[i-1]+h*f1(X[i-1],Y[i-1]);
        X[i]=X[i-1]+h;
        Y[i]=Y[i-1]+h*((f(X[i-1],Y[i-1])+f(X[i], y))/2);
        fprintf(output, "%f ", Y[i]);
    }
    fclose(output);
}

void method_runge_kutt(double h) {
    FILE *output;
    output = fopen("output.txt", "a+");
    fprintf(output,"\n%6s", "y_rk =");

    double n=(B-A)/h;
    double X[(int)n], Y[(int)n];
    X[0]=A; Y[0]=5;
    fprintf(output, "%f ", Y[0]);
    for(int i=1; i<=n; i++){
        double k1=f(X[i-1], Y[i-1]);
        double k2=f(X[i-1]+h/2, Y[i-1]+k1*h/2);
        double k3=f(X[i-1]+h/2, Y[i-1]+k2*h/2);
        double k4=f(X[i-1]+h, Y[i-1]+k3*h);
        Y[i] = Y[i-1]+h/6*(k1+2*k2+2*k3+k4);
        X[i] = X[i-1]+h;
        fprintf(output, "%f ", Y[i]);
    }
    fclose(output);
}

double f (double x, double y) {
	return (-x*(1+y)-y)/(pow(x,2)*y);
}
double f1 (double x, double y) {
	return (f(x,y)*pow(x,2)+(pow(y,2)+y)*x+2*pow(y,2))/(pow(y,2)*pow(x,3));
}

void print_n(double h){
    FILE *output;
    output = fopen("output.txt", "a+");
    fprintf(output,"\nh=%.2f", h);\
    fprintf(output,"\n%6s", "n ");
    double n=(B-A)/h;
    for(int i=0; i<=n; i++){
        fprintf(output, "%f ", A+i*h);
    }
    fclose(output);
}
