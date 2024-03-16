#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EXIT_SUCCESS 0
#define N 5
#define M 6

void method_Gauss();
void method_Gauss_Zeidel();
void read_data(float [N][M]);

int main(void) {
  method_Gauss();
  method_Gauss_Zeidel();
  return EXIT_SUCCESS;
}

void read_data(float a[N][M]){
    FILE *input;
    input = fopen("data.txt", "r");
    if(input==NULL){
        exit(1);
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            fscanf(input, "%f", &a[i][j]);
        }
    }
    fclose(input);
}

void method_Gauss() {
    float a[N][M]={{0}};
    read_data(a);

    int i, j, k;
    float factor, temp;
    float x[N];
    for (i = 0; i < N; i++) {
        x[i] = 0.0;
    }
    for (j = 0; j < N; j++) {
        for (i = 0; i < N; i++) {
            if (i > j) {
                factor = a[i][j] / a[j][j];
                for (k = 0; k < N; k++) {
                    a[i][k] -= a[j][k] * factor;
                }
                a[i][M-1] -= a[j][M-1] * factor;
            }
        }
    }
    for (i = N - 1; i >= 0; i--) {
        temp = a[i][M-1];
        for (j = i + 1; j < N; j++) {
            temp -= a[i][j] * x[j];
        }
        x[i] = temp / a[i][i];
    }
    
    FILE *output;
    output=fopen("answear_data.txt", "a+");
    fprintf(output,"method Gauss\na=%f b=%f c=%f d=%f e=%f\n",x[0], x[1], x[2], x[3], x[4]);
    fclose(output);
}

void method_Gauss_Zeidel(){
    float a[N][M] = {{0}};
    read_data(a);

    float old_x[N], new_x[N], error[N];
    for (int i = 0; i < N; i++) {
        old_x[i] = 0.0;
        new_x[i] = 0.0;
    }
    float max_error = 1, max_error_stage = 0.0, e=0.0001;
    while (max_error>e){
        new_x[0]=(a[0][N]-a[0][1]*old_x[1]-a[0][2]*old_x[2]-a[0][3]*old_x[3]-a[0][4]*old_x[4])/a[0][0];
        new_x[1]=(a[1][N]-a[1][0]*new_x[0]-a[1][2]*old_x[2]-a[1][3]*old_x[3]-a[1][4]*old_x[4])/a[1][1];
        new_x[2]=(a[2][N]-a[2][0]*new_x[0]-a[2][1]*new_x[1]-a[2][3]*old_x[3]-a[2][4]*old_x[4])/a[2][2];
        new_x[3]=(a[3][N]-a[3][0]*new_x[0]-a[3][1]*new_x[1]-a[3][2]*new_x[2]-a[3][4]*old_x[4])/a[3][3];
        new_x[4]=(a[4][N]-a[4][0]*new_x[0]-a[4][1]*new_x[1]-a[4][2]*new_x[2]-a[4][3]*new_x[3])/a[4][4];
        for(int i=0; i<N; i++){
            error[i]=fabs((new_x[i]-old_x[i])/new_x[i]);
            max_error_stage = (error[i]>max_error_stage)?error[i]:max_error_stage;
            old_x[i]=new_x[i];
        }
        max_error=max_error_stage;
        max_error_stage=0.0;
    }
    FILE *output;
    output=fopen("answear_data.txt", "a+");
    fprintf(output,"method Gauss Zeidel\na=%f b=%f c=%f d=%f e=%f\n",new_x[0], new_x[1], new_x[2], new_x[3], new_x[4]);
    fclose(output);
}





