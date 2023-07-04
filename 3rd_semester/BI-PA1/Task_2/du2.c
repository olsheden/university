#include <stdio.h>
#include <float.h>
#include <math.h>

bool DblEpsilon(double a, double b){
    return fabs(a-b) <= DBL_EPSILON * fmax(fabs(a), fabs(b)) * 1000;
}

int ErrorInp(){
    printf("Nespravny vstup.\n");
    return 1;
}

int input(double* x, double* y, char letter){
    printf("Bod %c:\n", letter);
    if(scanf(" %lf %lf", x, y) != 2) return ErrorInp();
    return 0;
}

char comp(double x1, double x2, double x3){
    if((x1 < x2 && x1 > x3) || (x1 > x2 && x1 < x3)) return 'A';
    else if((x2 < x1 && x2 > x3) || (x2 < x3 && x2 > x1)) return 'B';
    else return 'C';
}

int same(double x1, double y1,double x2, double y2,double x3, double y3){
    if((DblEpsilon(x1, x2) && DblEpsilon(y1, y2)) || (DblEpsilon(x1, x3) && DblEpsilon(y1, y3)) || (DblEpsilon(x2, x3) && DblEpsilon(y3, y2))){
        printf("Nektere body splyvaji.\n");
        return 1;
    }
    return 0;
}

void checkPoints(double x1, double y1,double x2, double y2,double x3, double y3){
    if(same(x1, y1, x2, y2, x3, y3)) return;
    if(DblEpsilon(x1, x2) && DblEpsilon(x2,x3) && DblEpsilon(x3,x1)) {
        printf("Body lezi na jedne primce.\n");
        printf("Prostredni je bod %c.\n", comp(y1, y2, y3));
        return;
    }
    else if((DblEpsilon(x1, x2) && !(DblEpsilon(x3,x2))) || (DblEpsilon(x2,x3) && !(DblEpsilon(x1,x3))) || (DblEpsilon(x1,x3) && !(DblEpsilon(x2,x1)))){
        printf("Body nelezi na jedne primce.\n");
        return;
    }
    double diffY = (y2-y1)/(x2-x1);
    double checkRes = y1+(diffY * (x3-x1));
    if(DblEpsilon(y3, checkRes)){
        printf("Body lezi na jedne primce.\n");
        printf("Prostredni je bod %c.\n", comp(x1, x2, x3));
        return;
    }
    else{
        printf("Body nelezi na jedne primce.\n");
        return;
    }
}

int main(){
    double x1, y1, x2, y2, x3, y3;
    if(input(&x1, &y1, 'A')) return 1;
    if(input(&x2, &y2, 'B')) return 1;
    if(input(&x3, &y3, 'C')) return 1;
    checkPoints(x1, y1, x2, y2, x3, y3);
    return 0;
}