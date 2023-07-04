#include <stdio.h>
#include <stdlib.h>


int Error(){
    printf("Nespravny vstup.\n");
    return 1;
}

int compareInt ( const int * x, const int * y ) {
    return *x - *y;
}

void countSameSums( int* sums, int iSum){
    int num = 0, serie = 1;
    for(int i =0; i < iSum-1; i++){
        if(sums[i] == sums[i+1]) {
            serie++;
        }
        else if(sums[i] != sums[i+1] && serie != 1){
            num += (serie * (serie-1)) / 2;
            serie = 1;
        }
        else serie = 1;
    }
    printf("Pocet dvojic: %d\n", num);
}

int sum(int start, int end, int array[]){
    int result = 0;
    for(int i = start; i <= end; i++){
        result += array[i];
    }
    return result;
}

void sumsOfNumbers(int array[], int amount){
    int start = 0, iSum = 0, end = amount;
    int sums[2000000];
    while(start != amount){
        sums[iSum++] = sum(start, end, array);
        end--;
        if(start == end) {
            end = amount;
            start++;
        }
    }
    qsort(sums, iSum, sizeof(sums[0]), (int(*)(const void *, const void *)) compareInt);
    countSameSums(sums, iSum);
}

int main(){
    int amount = 0, input;
    int array[4009];
    printf("Posloupnost:\n");
    while( (input = scanf(" %d", &array[amount])) != EOF){
        if(input != 1) return Error();
        if(amount > 2000) return Error();
        amount++;
    }
    if(amount > 2000) return Error();
    if(amount == 0) return Error();
    sumsOfNumbers(array, amount-1);
    return 0;
}