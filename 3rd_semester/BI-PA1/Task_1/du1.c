#include <stdio.h>
#include <math.h>

int Error(){
    printf("Nespravny vstup.\n");
    return 1;
}

int input(double* kr_ur, double* db_ur){
    printf("Zadejte kreditni urok [%%]:\n");
    if(scanf(" %lf", kr_ur) != 1 || *kr_ur <= 0) return Error();
    *kr_ur = (*kr_ur)/100;
    printf("Zadejte debetni urok [%%]:\n");
    if(scanf(" %lf", db_ur) != 1 || *db_ur <= 0) return Error();
    *db_ur = (*db_ur)/100;
    return 0;
}

void percents(double* balance, int times, double kr_ur, double db_ur){
    if(*balance < 0) {
        for(int i = 0; i < times; i++) *balance += (ceil((*balance)*db_ur*100))/100;
    } 
    else {
        for(int i = 0; i < times; i++) *balance += (floor((*balance)*kr_ur*100))/100;
    }
}

int transactions(double kr_ur, double db_ur){
    double balance = 0;
    double day, diff;
    int prev = -1, period = 0;
    printf("Zadejte transakce:\n");
    while(true){
        if(scanf(" %lf , %lf", &day, &diff) != 2 || day != (int)day || diff != (int)diff || day <= prev) return Error();
        if(prev != -1) period = day - prev;
        prev = day;
        if(balance != 0) percents(&balance, period, kr_ur, db_ur);
        if(diff == 0) break;
        balance += diff;
    }
    printf("Zustatek: %.2f\n", balance);
    return 0;
}



int main(){
    double kr_ur, db_ur;
    if(input(&kr_ur, &db_ur)) return 1;
    transactions(kr_ur, db_ur);


    return 0;
}