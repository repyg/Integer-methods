/*
＼　　ヽ　　　　i　　|　　　　 /　　　/　
　　　＼　
　　　　　　　　　　　　　　;' ':;,,　　　　 ,;'':;,
　　　　　　　　　　　　　;'　　 ':;,.,.,.,.,.,,,;'　　';,
　　ー　　　　　　　　 ,:'　　　　　　　　 　::::::::､
　_＿　　　　　　　　,:' ／ 　 　　　　＼ 　　::::::::', Have A Good day
　　　　　二　　　　:'　 ●　　　　　 ●　 　　 ::::::::i.
　　￣　　　　　　　i　 '''　(__人_)　　'''' 　　 ::::::::::i
　　　　-‐　　　　　 :　 　　　　　　　　　 　::::::::i
　　　　　　　　　　　`:,､ 　　　　　 　 　 :::::::::: /
　　　　／　　　　　　 ,:'　　　　　　　 : ::::::::::::｀:､
　　　　　　　　　　　 ,:'　　　　　　　　 : : ::::::::::｀:､
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EXIT_SUCCESS 0
#define N 6
#define M 9


void method_mnk();
void method_Gauss(double a[N][N+1], double x[N]);

int main(void) {
  method_mnk();
  return EXIT_SUCCESS;
}

void method_mnk(){
    float experimental_x[M], experimental_y[M];

    FILE *input;
    input=fopen("input_data.txt", "r");
    if(input==NULL)
        exit(1);    
    for(int i=0; i<M; i++)
        fscanf(input, "%f ", &experimental_x[i]);
    for(int i=0; i<M; i++)
        fscanf(input, "%f ", &experimental_y[i]);
    
    fclose(input);

    double S[(N-1)*2+1], Sy[N];
    S[0]=M;
    for(int i=0; i<M; i++){
        for(int j=1; j<=(N-1)*2; j++)
            S[j]+=pow(experimental_x[i], j);
        Sy[0]+=experimental_y[i];
        for(int j=1; j<N; j++)
            Sy[j]+=(experimental_y[i]*pow(experimental_x[i], j));
    }

    double a[N][N+1];
    for(int i=0; i<N;i++){
        for(int j=0; j<N;j++){
            a[i][j]=S[i+j];
        }
        a[i][N]=Sy[i];
    }
    FILE *output;
    output= fopen("output.txt", "w");
    for(int i=0; i<N;i++)
        fprintf(output, "a0*(%f) + a1*(%f) + a2*(%f) + a3*(%f) + a4*(%f) + a5*(%f) = %f\n",
         a[i][0], a[i][1], a[i][2], a[i][3], a[i][4], a[i][5], a[i][6]);
    
    double x[N];
    for (int i = 0; i < N; i++) 
        x[i] = 0.0;

    method_Gauss(a, x);
    
    double R=0.0;
    for(int i=0; i<M;i++)
        R+=pow(((x[0]+x[1]*experimental_x[i]+x[2]*pow(experimental_x[i],2)+x[3]*pow(experimental_x[i],3)+x[4]*pow(experimental_x[i],4)+x[5]*pow(experimental_x[i],5))-experimental_y[i]),2);

    for(int i =0; i<N;i++)
        printf("%f ", x[i]);
    fprintf(output, "%f + (%f)*x + (%f)*x^2 + (%f)*x^3 + (%f)*x^4 + (%f)*x^5 = y\nR = %f", x[0], x[1], x[2], x[3], x[4], x[5], R);
    fclose(output);
}

void method_Gauss(double a[N][N+1], double x[N]){
    double factor, temp;
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            if (i > j) {
                factor = a[i][j] / a[j][j];
                for (int k = 0; k < N; k++)
                    a[i][k] -= a[j][k] * factor;
                a[i][N] -= a[j][N] * factor;
            }
        }
    }
    for (int i = N-1; i >= 0; i--) {
        temp = a[i][N];
        for (int j = i + 1; j < N; j++)
            temp -= a[i][j] * x[j];
        x[i] = temp / a[i][i];
    }
}
