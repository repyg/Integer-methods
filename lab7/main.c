#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define EXIT_SUCCESS 0
#define NUM_COMMANDS 1

int f(double, double);
void  method_Monte_Carlo(int);

int main(void) {
    int n[8]={5000, 10000, 25000, 50000, 100000, 200000, 500000, 1000000};
    for(int i=0; i<8;i++){
        method_Monte_Carlo(n[i]);
    }
    FILE *gnuPipe = NULL;
    gnuPipe = _popen("gnuplot -p", "w");
    char *GnuCommands[]={"plot 'text.txt' u 1:2 w l"};
    for(int i=0; i<NUM_COMMANDS; i++)
        fprintf(gnuPipe, "%s\n", GnuCommands[i]);
    pclose(gnuPipe);
    return EXIT_SUCCESS;
}

int f(double x, double y){
    if ((y<=(log(cos(x)))) && (y>=(2*pow(x,2)-2)) && y<=log(x))
        return 1;
    else
        return 0;
}

void  method_Monte_Carlo(int n){
    double ax=0.0, bx=1.0, ay=-2.0, by=0.0;
    srand(time(NULL));
    int m=0;
    for(int i=0; i<n; i++){
        m+=f(((double)rand()/RAND_MAX*(bx-ax)+ax),((double)rand()/RAND_MAX*(by-ay)+ay));
    }
    FILE *output;
    output= fopen("output.txt", "a+");
    fprintf(output,"%d - %f\n", n, (double)m/n*fabs((by-ay)*(bx-ax)));
    fclose(output);
}