#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

////////////////////////////////////////////////CHECK Inputs////////////////////////////////////////////////////////////////////////
int isNotLeap(long long int y){
    if(y % 4000 == 0) return 1;
    else if(y % 1000 == 0) return 0;
    else if(y % 400 == 0) return 0;
    else if(y % 100 == 0) return 1;
    else if(y % 4 == 0) return 0;   
    else return 1;
}

int daysAmount(int m, long long int y){
    if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) return 31;
    else if ( m == 4 || m == 6 || m == 9 || m == 11) return 30;
    else if(isNotLeap(y)) return 28;
    else return 29;
}

int checkDate(long long int y,  int m,  int d,  int h,  int i){
    if( m < 1 || m > 12 || d < 1 || d > daysAmount(m,y) || h < 0 || h > 23 || i < 0 || i > 59) return 1;
    return 0;
}

int checkDates(long long int y1, int m1, int d1, int h1,  int i1, long long int y2,  int m2, int d2, int h2,int i2){
    if(checkDate(y1, m1, d1, h1, i1)) return 1;
    if(checkDate(y2, m2, d2, h2, i2)) return 1;
    if((y1 > y2) || (y1 == y2 && m1 > m2) || (y1 == y2 && m1 == m2 && d1 > d2) || (y1 == y2 && m1 == m2 && d1 == d2 && h1 > h2) || (y1 == y2 && m1 == m2 && d1 == d2 && h1 == h2 && i1 > i2)) return 1;
    return 0;
}

int dayCode(int day, int month, long long int year){
    return (day += month < 3 ? year-- : year - 2, 23*month/9 + day + 4 + year/4- year/100 + year/400)%7;
}

//////////////////////////////////////////////////Calculators/////////////////////////////////////////////////////////////////////

void countMins(int i,  int lim, long long int * b1){
    if(i % 15 != 0)i += (15 - i % 15);
    for(int ii = i; ii  <= lim; ii+=15){
        if(ii == 0) * b1 += 4;
        else if(ii == 15) (*b1)++;
        else if( ii == 30) *b1 += 2;
        else if(ii == 45) *b1 += 3;
    }
}

void countHours(int h, int lim, long long int * b1, long long int * b2){
    for(int i = h; i  <= lim; i++){
        *b1 += 10;
        if(i == 0 || i == 12) *b2 += 12;
        else *b2 += (i % 12);
    }
}

void countDays(int d, int lim, long long int * b1, long long int * b2, int m, long long int y){
    int oneDay_b1 = 240, oneDay_b2 = 156;
    for(int i = d; i <= lim; i++){
        if(dayCode(i, m, y) != 0){
            *b1 += oneDay_b1; 
            *b2 += oneDay_b2;
        }
    }
}

void countMonths(int m, int lim, long long int * b1, long long int * b2, long long int y, int d){
    int oneDay_b1 = 240, oneDay_b2 = 156;
    for(int i = m; i <= lim; i++){
        if(daysAmount(i, y) == 28){
            *b1 += oneDay_b1 * 28;
            *b2 += oneDay_b2 * 28;
            *b1 -=  4 * 240;
            *b2 -= 4 * 156;
        }
        else if(daysAmount(i, y) == 29){
            *b1 += oneDay_b1 * 29;
            *b2 += oneDay_b2 * 29;
            if( dayCode(1, i, y) == 0) {
                *b1 -=  5 * 240;
                *b2 -= 5 * 156;
            }
            else{
                *b1 -= 4 * 240;
                *b2 -= 4 * 156;
            } 
        }
        else{
            *b1 += oneDay_b1 * daysAmount(i, y);
            *b2 += oneDay_b2 * daysAmount(i, y);
            if( daysAmount(i, y) == 31) {
                if( dayCode(1, i, y) == 0 || dayCode(1, i, y) == 5 || dayCode(1,i,y) == 6) {
                    *b1 -=  5 * 240;
                    *b2 -= 5 * 156;
                }
                else{
                    *b1 -= 4 * 240;
                    *b2 -= 4 * 156;
                } 
            }
            else{
                if( dayCode(1, i, y) == 0 || dayCode(1,i,y) == 6) {
                    *b1 -=  5 * 240;
                    *b2 -= 5 * 156;
                }
                else{
                    *b1 -= 4 * 240;
                    *b2 -= 4 * 156;
                }
            } 
        }
    }

}

void countYears(long long int y1, long long int y2, long long int * b1, long long int * b2){
    for(int i = y1; i <= y2; i++){
        if(isNotLeap(i)){           
            if( dayCode(1, 1, i) == 0) {
                *b1 -=  53 * 240;
                *b2 -= 53 * 156;
            }
            else{
                *b1 -= 52 * 240;
                *b2 -= 52 * 156;
            } 
            *b1 += 87600;
            *b2 += 56940;
        }
        else{
            if( dayCode(1, 1, i) == 6 || dayCode(1, 1, i) == 0) {
                *b1 -=  53 * 240;
                *b2 -= 53 * 156;
            }
            else{
                *b1 -= 52 * 240;
                *b2 -= 52 * 156;
            } 
            *b1 += 87840;
            *b2 += 57096;
        }
    }
}

///////////////////////////////////////////////////BELLS//////////////////////////////////////////////////////////////////////////

void countBells(long long int y1, int m1,  int d1,  int h1, int i1, long long int y2,  int m2,  int d2, int h2, int i2, long long int * b1, long long int * b2 ){
    *b1 = 0;
    *b2 = 0;
    if(h1 == h2 && d1 == d2 && m1 == m2 && y1 == y2){
       if(dayCode(d1, m1, y1) != 0){
            if(i1 == 0 || i2 == 0) {
                if(h2 == 12 || h2 == 0) *b2 += 12;
                else *b2 += (h2 % 12);
            }
       }
        if(dayCode(d1, m1, y1) != 0)countMins(i1, i2, b1);
        return;
    }
    else{
        if(i1!=0){
            if(dayCode(d1, m1, y1) != 0)countMins(i1, 45, b1);
            if(h1 == 23){
                h1 = 0;
                if(d1 == daysAmount(m1, y1) )
                {
                    d1 = 1;
                    if(m1 == 12){
                        m1 = 1;
                        y1++;
                    }
                    else m1++;
                }
                else d1++;
            }
            else h1++;
            i1 = 0;
        }
        if(dayCode(d2, m2, y2) != 0)countMins(i1, i2, b1);
    }
    if(d1 == d2 && m1 == m2 && y1 == y2){
        if(dayCode(d1, m1, y1) != 0) countHours(h1, h2-1, b1, b2);
        h1 = h2;
        if(dayCode(d2, m2, y2) != 0 && i1 == 0){
            countHours(h1, h2-1, b1, b2);
            if(h2 == 12 || h2 == 0) *b2 += 12;
            else *b2 += (h2 % 12);
        }
        return;
    }
    else{
        if(h1 != 0){
            if(dayCode(d1, m1, y1) != 0)countHours(h1, 23, b1, b2);
            if(d1 == daysAmount(m1, y1))
            {
                d1 = 1;
                if(m1 == 12){
                    m1 = 1;
                    y1++;
                }
                else m1++;
            }
            else d1++;
            h1 = 0;
        }
        if(dayCode(d2, m2, y2) != 0 && i1 == 0){
            countHours(h1, h2-1, b1, b2);
            if(h2 == 12 || h2 == 0) *b2 += 12;
            else *b2 += (h2 % 12);
        }
    }
    // DAYS
    if(m1 == m2 && y1 == y2){
        countDays(d1, d2-1, b1, b2, m1, y1);
        return;
    }
    else{
        if(d1 != 1){
            countDays(d1, daysAmount(m1, y1), b1, b2, m1, y1);
            d1 = 1;
            if(m1 == 12){
                m1 = 1;
                y1++;
            }
            else m1++;
        }
        countDays(d1, d2-1, b1, b2, m2, y2);
        
    }
    if(y1 == y2){
        countMonths(m1, m2-1, b1, b2, y1, d1);
        return;
    }
    else{
        if(m1 != 1){
            countMonths(m1, 12, b1, b2, y1, d1);
            m1 = 1;
            y1++;
        }
        countMonths(m1, m2-1, b1, b2, y2, d2);
    }
    countYears(y1, y2-1, b1, b2);
    return;
}
//b1 - mins; b2 - hours
int bells ( long long int y1, int m1, int d1, int h1, int i1, long long int y2, int m2, int d2, int h2, int i2, long long int * b1, long long int * b2 )
{
    if(checkDates( y1, m1, d1, h1, i1, y2, m2, d2, h2, i2)) return 0;
    countBells( y1, m1, d1, h1, i1, y2, m2, d2, h2, i2, b1, b2);
    return 1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    // long long int b1, b2;
    
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
