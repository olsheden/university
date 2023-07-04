#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

int Error(){                        //Function to display an Error, if input was in wrong format
    printf("Nespravny vstup.\n");
    return 1;
}

bool cmpDoubleSmall(double a, double b){                                   //Func to compare small values of double
    return fabs(a-b) <= DBL_EPSILON * fmax(fabs(a), fabs(b)) * 1000;
}

bool cmpDoubleBig(double a, double b){                                   //Func to compare big values of double
    return fabs(a-b) <= DBL_EPSILON * fmax(fabs(a), fabs(b)) * 10e-9;
}


typedef struct Planes {         //struct that contains all of the data of planes
    char name[200];
    double x;
    double y;
}Plane;

int fInput( Plane** air, int* amount){              //function that implements the input of the data of planes located in air
    int i = 0, input;
    printf("Pozice letadel:\n");
    while((input = scanf(" %lf, %lf : %199s", &(*air)[i].x, &(*air)[i].y, (*air)[i].name)) != EOF){
        if(input != 3) return Error();
        i++;
        if(i == *amount){
            (*amount) += 100;
            (*air) = (Plane*)realloc((*air), (*amount)*(sizeof(Plane)));
        }
    }
    if(i < 2) return Error();                       //controls the amount of planes
    (*amount) = i-1;
    return 0;
}

void printResult(double minRange, int numOfRes, char** memory){   //displays the smallest range and pairs of planes in it
    printf("Vzdalenost nejblizsich letadel: %lf\n", minRange);
    printf("Nalezenych dvojic: %d\n", (numOfRes+1)/2);
    for(int i = 0; i < numOfRes; i+=2){
        printf("%s - %s\n", memory[i], memory[i+1]);
    }
}

void countRange(Plane* air, int amount){            //function to find the closest pairs of planes
    int sizeMemory = 10, numOfRes = 0;
    char** memory = (char**)malloc(sizeMemory*(sizeof(*memory)));           //our array, that will store data about the closest planes
    double minRange, newRange;
    minRange = sqrt(pow(air[0].x - air[1].x, 2) + pow(air[0].y - air[1].y, 2));     //formula, that counts the range between two planes
    memory[numOfRes++] = air[0].name;
    memory[numOfRes++] = air[1].name;
    for(int first = 0; first < amount; first++){
        for(int second = first+1; second <= amount; second++){
            newRange = sqrt(pow(air[first].x - air[second].x, 2) + pow(air[first].y - air[second].y, 2));
            if( (cmpDoubleSmall(minRange, newRange) || cmpDoubleBig(minRange, newRange)) && !(first == 0 && second == 1)){  //if we have found planes with our smallest range, store it
                memory[numOfRes++] = air[first].name;
                memory[numOfRes++] = air[second].name;
                if(numOfRes == sizeMemory){
                    sizeMemory += 20;
                    memory = (char**)realloc(memory, sizeMemory*(sizeof(*memory)));
                }
            }
            else if( (newRange < minRange) && !(first == 0 && second == 1)){        //if we have found new the smallest range, we will store it
                minRange = newRange;
                numOfRes = 0;
                memory[numOfRes++] = air[first].name;
                memory[numOfRes++] = air[second].name;
            }
        }
    }
    printResult(minRange, numOfRes, memory);                 // prints the result
    free(memory);                                   //freeing the memory
}


int main(){
    int amount = 10;
    Plane* air = (Plane*)malloc(amount * sizeof(*air));         //array of struct, that contains all data about every plane
    
    if(fInput(&air, &amount)){
        free(air);                                   //In case of wrong input, I'm freeing the memory, that was allocate for our array 
        return 1;
    } 

    countRange(air, amount);
    
    free(air);                                          //freeing the array of struct
    return 0;
}