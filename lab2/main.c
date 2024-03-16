#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EXIT_SUCCESS 0
#define E 0.0001
#define A -0.75
#define B 0
#define calculated_value_integral 2.0667

void method_right_rectangle();
void method_left_rectangle();
void method_middle_rectangle();
void method_trapeze();
void method_simpson();
double f(double);

int main(void) {
  method_right_rectangle();
  method_left_rectangle();
  method_middle_rectangle();
  method_trapeze();
  method_simpson();
  return EXIT_SUCCESS;
}

void method_right_rectangle(){
  FILE *output;
  output = fopen("output.txt", "a+");
  fprintf(output, "method right rectangle\n%10s%10s%10s%10s\n","n", "h","S","ΔS");

  int n = 10;
  double S1=0, S2=0, h, sum;
  for(int i=0; i<2; i++){
    h =(B-A)/n;
    sum = 0.0;
    for(int j=1; j<=n; j++)
      sum+=h*f(A+j*h);
    S1 = S2;
    S2 = sum;
    fprintf(output, "%10d%10.4f%10.4f%10.4f\n",n, h,sum,fabs(sum-calculated_value_integral));
    n*=2;
  }
  while(fabs(S1-S2)>E){
    h =(B-A)/n;
    sum = 0.0;
    for(int i=1; i<=n; i++)
      sum+=h*f(A+i*h);
    S1 = S2;
    S2 = sum;
    fprintf(output, "%10d%10.4f%10.4f%10.4f\n",n, h,sum,fabs(sum-calculated_value_integral));
    n*=2;
  }
  fclose(output);
}

void method_left_rectangle(){
  FILE *output;
  output = fopen("output.txt", "a+");
  fprintf(output, "method left rectangle \n%10s%10s%10s%10s\n","n", "h","S","ΔS");

  int n = 10;
  double S1=0, S2=0, h, sum;
  for(int i=0; i<2; i++){
    h =(B-A)/n;
    sum = 0.0;
    for(int j=0; j<n; j++)
      sum+=h*f(A+j*h);
    S1 = S2;
    S2 = sum;
    fprintf(output, "%10d%10.4f%10.4f%10.4f\n",n, h,sum,fabs(sum-calculated_value_integral));
    n*=2;
  }
  while(fabs(S1-S2)>E){
    h =(B-A)/n;
    sum = 0.0;
    for(int i=0; i<n; i++)
      sum+=h*f(A+i*h);
    S1 = S2;
    S2 = sum;
    fprintf(output, "%10d%10.4f%10.4f%10.4f\n",n, h,sum,fabs(sum-calculated_value_integral));
    n*=2;
  }
  fclose(output);
}

void method_middle_rectangle(){
  FILE *output;
  output = fopen("output.txt", "a+");
  fprintf(output, "method middle rectangle\n%10s%10s%10s%10s\n","n", "h","S","ΔS");
  
  int n = 10;
  double S1=0, S2=0, h, sum;
  for(int i=0; i<2; i++){
    h =(B-A)/n;
    sum = 0.0;
    for(int j=0; j<n; j++)
      sum+=h*f(A+(j+0.5)*h);
    S1 = S2;
    S2 = sum;
    fprintf(output, "%10d%10.4f%10.4f%10.4f\n",n, h,sum,fabs(sum-calculated_value_integral));
    n*=2;
  }
  while(fabs(S1-S2)>E){
    h =(B-A)/n;
    sum = 0.0;
    for(int i=0; i<n; i++)
      sum+=h*f(A+(i+0.5)*h);
    S1 = S2;
    S2 = sum;
    fprintf(output, "%10d%10.4f%10.4f%10.4f\n",n, h,sum,fabs(sum-calculated_value_integral));
    n*=2;
  }

  fclose(output);
}

void method_trapeze(){
  FILE *output;
  output = fopen("output.txt", "a+");
  fprintf(output, "method trapeze\n%10s%10s%10s%10s\n","n", "h","S","ΔS");

  int n = 10;
  double S1=0, S2=0, h, sum;
  for(int i=0; i<2; i++){
    h =(B-A)/n;
    sum = 0.0;
    for(int j=0; j<n; j++)
      sum+=(f(A+j*h)+f(A+(j+1)*h))*h/2;
    S1 = S2;
    S2 = sum;
    fprintf(output, "%10d%10.4f%10.4f%10.4f\n",n, h,sum,fabs(sum-calculated_value_integral));
    n*=2;
  }
  while(fabs(S1-S2)>E){
    h =(B-A)/n;
    sum = 0.0;
    for(int i=0; i<n; i++)
      sum+=(f(A+i*h)+f(A+(i+1)*h))*h/2;
    S1 = S2;
    S2 = sum;
    fprintf(output, "%10d%10.4f%10.4f%10.4f\n",n, h,sum,fabs(sum-calculated_value_integral));
    n*=2;
  }

  fclose(output);
}

void method_simpson(){
  FILE *output;
  output = fopen("output.txt", "a+");
  fprintf(output, "method Simpson\n%10s%10s%10s%10s\n","n", "h","S","ΔS");

  int n = 10;
  double S1=0, S2=0, h, sum;
  for(int i=0; i<2; i++){
    h =(B-A)/n;
    sum = 0.0;
    for(int j=0; j<n; j++)
      sum+=h/6.0*(f(A+j*h) + 4.0*f(0.5*(A+j*h+A+(j+1)*h)) + f(A+(j+1)*h));
    S1 = S2;
    S2 = sum;
    fprintf(output, "%10d%10.4f%10.4f%10.4f\n",n, h,sum,fabs(sum-calculated_value_integral));
    n*=2;
  }
  while(fabs(S1-S2)>E){
    h =(B-A)*n;
    sum = 0.0;
    for(int i=0; i<n; i++)
      sum+=h/6.0*(f(A+i*h) + 4.0*f(0.5*(A+i*h+A+(i+1)*h)) + f(A+(i+1)*h));
    S1 = S2;
    S2 = sum;
    fprintf(output, "%10d%10.4f%10.4f%10.4f\n",n, h,sum,fabs(sum-calculated_value_integral));
    n*=2;
  }

  fclose(output);
}

double f(double x){
  return (5*x)/(pow(x,2)-1);
}
