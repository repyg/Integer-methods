#include <stdio.h>
#include <stdlib.h>
#include <sys\time.h>

#define EXIT_SUCCESS 0
#define A -25000
#define B 25000
#define N 100000

void generation();
void read_file(int [N]);
void method_simple_sort();
void method_puzirek();
void method_comb_sort();
void method_shaker_sorting();

int main(void) { 
  FILE *output;
  output = fopen("output.txt", "a+");
  fprintf(output,"Working hours and number of permutations for %d\n", N);
  fclose(output);
  generation();
  method_simple_sort();
  method_puzirek();
  method_comb_sort();
  method_shaker_sorting();
  return EXIT_SUCCESS;
}

void generation(){
  FILE *input;
  input=fopen("input.txt","a+");
  srand(time(NULL));
  for(int i = 0; i<N; i++){
    fprintf(input, "%d ", A+rand()%(B-A+1));
  }
  fclose(input);
}

void read_file(int array[N]){
  FILE *input;
  input=fopen("input.txt","r");
  for(int i=0; i<N; i++){
    fscanf(input,"%d ", &array[i]);
  }
  fclose(input);
}

void method_simple_sort() {
  time_t start,end;
  int array[N], number_permutations=0;
  read_file(array);
  
  start = clock();
  for(int k=0; k<N-1; k++){
    int ind_max = k;
    for(int i=1+k;i<N;i++)
      if (array[i]>array[ind_max])
        ind_max = i;
    int temp = array[k];
    array[k] = array[ind_max];
    array[ind_max]=temp;
    number_permutations++;
  }
  end = clock();

  FILE *output;
  output = fopen("output.txt", "a+");
  fprintf(output, "The sorting time by the simple selection method %f and the number of exchange operations %d\n",
  (double)(end - start)/(CLOCKS_PER_SEC), number_permutations);
  fclose(output);
}

void method_puzirek() {
  time_t start,end;
  int array[N] = {0};
  unsigned long long int number_permutations = 0;
  read_file(array);
  
  int count = 1;
  start = clock();
  while (count > 0) { 
    count = 0; 
    for (int i = 0; i < N - 1; i++) { 
	    if(array[i] > array[i + 1]) { 
	      int temp = array[i]; 
	      array[i] =array[i + 1]; 
        array[i + 1] = temp; 
        count++;
        number_permutations++;
      } 
    } 
  }
  end = clock(); 

  FILE *output;
  output = fopen("output.txt", "a+");
  fprintf(output, "The sorting time by the bubble method %f and the number of exchange operations %d\n",
  (double)(end - start)/(CLOCKS_PER_SEC), number_permutations);
  fclose(output);
}

void method_comb_sort () {
  time_t start,end;
  int array[N] = {0}, number_permutations = 0;
  read_file(array);

  double fakt = 1.2473309;
  int step = N - 1;
  start = clock();
  while (step >= 1){
    for (int i = 0; i + step < N; ++i) {
      if (array[i] > array[i + step]) {
        int temp =  array[i + step];
        array[i + step] = array[i];
        array[i] = temp;
        number_permutations++;
      } 
    } 
    step /= fakt;
  }  
  end = clock(); 
  FILE *output;
  output = fopen("output.txt", "a+");
  fprintf(output, "The sorting time by the comb sorting method %f and the number of exchange operations %d\n",
  (double)(end - start)/(CLOCKS_PER_SEC), number_permutations);
  fclose(output);
}

void method_shaker_sorting(){
  time_t start,end;
  int array[N] = {0}, number_permutations = 0;
  read_file(array);

  int left = 0, right = N - 1;
  int flag = 1;
  start = clock();
  while ((left < right) && flag > 0){
    flag = 0;
    for (int i = left; i<right; i++){
      if (array[i]>array[i + 1]){
        double t = array[i];
        array[i] = array[i + 1];
        array[i + 1] = t;
        flag = 1;   
        number_permutations++;  
      }
    }
    right--; 
    for (int i = right; i>left; i--){
      if (array[i - 1]>array[i]) {           
        double t = array[i];
        array[i] = array[i - 1];
        array[i - 1] = t;
        flag = 1;
        number_permutations++; 
      }
    }
    left++; 
  }
  end = clock(); 

  FILE *output;
  output = fopen("output.txt", "a+");
  fprintf(output, "The sorting time by the shaker sorting method %f and the number of exchange operations %d\n",
  (double)(end - start)/(CLOCKS_PER_SEC), number_permutations);
  fclose(output);
}