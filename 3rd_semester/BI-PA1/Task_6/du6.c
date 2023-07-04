#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

/////////////////////////////////////////////////////STRUCTS////////////////////////////////////////////////

typedef struct finalProds{
    char* nameShelf;
    char* nameProd;
    int numOfShlf;
}finalProd;

typedef struct Shelves{
    char** list;
    int amount;
    struct Shelves* next;
}Shelf;

//////////////////////////////////////////////////////ERRORS///////////////////////////////////////////
int Error(){
    printf("Nespravny vstup.\n");
    return 1;
}

/////////////////////////////////////////////////////FUNCTIONS////////////////////////////////////////////

int shlvCompare(const void *x, const void *y){
    finalProd* prodx = (finalProd*)x;
    finalProd* prody = (finalProd*)y;
    return (prodx->numOfShlf - prody->numOfShlf);
}

void clean(Shelf* shelf){
    while(shelf){
        Shelf* tmp = shelf->next;
        for(int i = 0; i < shelf->amount; i++) free(shelf->list[i]);
        free(shelf->list);
        free(shelf);
        shelf = tmp;
    }
}

char * removeEnd(char* str){
    str[strlen(str)-1] = '\0';
    return str;
}

void cleanArr(finalProd* result, int numOfShlvs){
    for(int i = 0; i < numOfShlvs; i++){
        free(result[i].nameProd);
        free(result[i].nameShelf);
    }
    free(result);
}

void print(Shelf* shelf){
    if(shelf){
        printf("/////////\n");
        for(int i = 0; i < shelf->amount; i++) printf("%s",shelf->list[i]);
        printf("/////////\n");
        print(shelf->next);
    }    
}

void printRes(finalProd* result, int numOfShlvs){
    for(int i = 0; i < numOfShlvs; i++){
        printf(" %d. %s -> #%d %s\n", i, result[i].nameProd, result[i].numOfShlf, result[i].nameShelf);
    }
}

char * lowerCase(char* str){
    int len = strlen(str);
    for(int i = 0; i < len; i++){
        str[i] = tolower(str[i]);
    }
    return str;
}

int checkNumber(char* str, int number){
    if(str[strlen(str)-1] == '\n') str[strlen(str)-1] = '\0';
    int len = strlen(str)-1;
    for(int i = 1; i <= len; i++){
        if(!isdigit(str[i])) return 1;
    }
    if(str[0] != '#') return 1;
    for(int i = 1; i <= len; i++){
        if(((int)((number*1.0)/pow(10.0, len-i))) != str[i] - '0' ) return 1;
        number%=(int)pow(10.0, len-i);
    }
    return 0;
}

int input(Shelf** shelf, int* number){
    int i = 0;
    Shelf* tmp = (Shelf*)malloc(sizeof(*tmp));
    tmp->amount = 5;
    tmp->list = (char**)malloc(tmp->amount*sizeof(*tmp->list));
    tmp->next = NULL;
    char str[100000];
    int check = 0;
    while(1){
        fgets(str, 100000, stdin);
        if(check == 0 && (*number) == 0){
            if(str[0] == '#' && str[1] == '0' && check == 0) {
                check += 1;
            }
            else if(str[0] != '#' && str[1] != '0' && check == 0){
                tmp->amount = i;
                check++;
                for(int i = 0; i < tmp->amount; i++) free(tmp->list[i]);
                free(tmp->list);
                free(tmp);
                return Error();
            }
        }
        if(feof(stdin)) {
            tmp->amount = i;
            for(int i = 0; i < tmp->amount; i++) free(tmp->list[i]);
            free(tmp->list);
            free(tmp);
            return Error();
        }
        if(str[0] == '#') {
            if(checkNumber(str, *number)) {
                tmp->amount = i;
                for(int i = 0; i < tmp->amount; i++) free(tmp->list[i]);
                free(tmp->list);
                free(tmp);
                return Error();
            }
            tmp->amount = i;
            (*shelf) = tmp;
            (*number)++;
            return input(&(*shelf)->next, number);
        }
        else if(str[0] == '\n'){
            tmp->amount = i;
            (*shelf) = tmp;
            break;
        }
        if(str[strlen(str)-1] == '\n') str[strlen(str)-1] = '\0';
        tmp->list[i] = (char*)malloc((strlen(str)+1)*sizeof(char));
        strcpy(tmp->list[i++], str);
        if( i == tmp->amount){
            tmp->amount *= 2;
            tmp->list = (char**)realloc(tmp->list,tmp->amount*(sizeof(*tmp->list)));
        }
    }
    return 0;
}

int findProdSame(Shelf* shelf, char* str, int number, finalProd** result, int* size, int* numOfShlvs){
    char* tmp = (char*)malloc((strlen(str)+1)*sizeof(char));
    strcpy(tmp, str);
    tmp = lowerCase(tmp);
    for(int i = 0; i < shelf->amount; i++){
        char* tmp2 = (char*)malloc((strlen(shelf->list[i])+1)*sizeof(char));
        strcpy(tmp2, shelf->list[i]);
        tmp2 = lowerCase(tmp2);
        if(!strcmp(tmp2,tmp)){
            free(tmp);
            free(tmp2);
            (*result)[(*numOfShlvs)].nameProd = (char*)malloc((strlen(str)+1)*sizeof(char));
            strcpy((*result)[(*numOfShlvs)].nameProd, str);
            (*result)[(*numOfShlvs)].nameShelf = (char*)malloc((strlen(shelf->list[i])+1)*sizeof(char));
            strcpy((*result)[(*numOfShlvs)].nameShelf, shelf->list[i]);
            (*result)[(*numOfShlvs)++].numOfShlf = number;
            if((*numOfShlvs) == (*size)){
                (*size)*=2;
                (*result) = (finalProd*)realloc((*result), (*size)*sizeof(*(*result)));
            }
            return 0;
        }
        free(tmp2);
    }
    number++;
    free(tmp);
    if(shelf->next) return findProdSame(shelf->next, str, number, result, size, numOfShlvs);
    return 1;
}

int findProdSub(Shelf* shelf, char* str, int number, finalProd** result, int* size, int* numOfShlvs){
    char* tmp = (char*)malloc((strlen(str)+1)*sizeof(char));
    strcpy(tmp, str);
    tmp = lowerCase(tmp);
    for(int i = 0; i < shelf->amount; i++){
        char* tmp2 = (char*)malloc((strlen(shelf->list[i])+1)*sizeof(char));
        strcpy(tmp2, shelf->list[i]);
        tmp2 = lowerCase(tmp2);
        if(strstr(tmp2,tmp) != NULL){
            free(tmp);
            free(tmp2);
            (*result)[(*numOfShlvs)].nameProd = (char*)malloc((strlen(str)+1)*sizeof(char));
            strcpy((*result)[(*numOfShlvs)].nameProd, str);
            (*result)[(*numOfShlvs)].nameShelf = (char*)malloc((strlen(shelf->list[i])+1)*sizeof(char));
            strcpy((*result)[(*numOfShlvs)].nameShelf, shelf->list[i]);
            (*result)[(*numOfShlvs)++].numOfShlf = number;
            if((*numOfShlvs) == (*size)){
                (*size)*=2;
                (*result) = (finalProd*)realloc((*result), (*size)*sizeof(*(*result)));
            }
            return 0;
        }
        free(tmp2);
    }
    number++;
    free(tmp);
    if(shelf->next) return findProdSub(shelf->next, str, number, result, size, numOfShlvs);
    return 1;
}

void printNA(char** notAvalaible, int iNA, int serie){
    for(int i = 0; i < iNA; i++){
        printf(" %d. %s -> N/A\n", serie, notAvalaible[i]);
        serie++;
    }
}

int searching( Shelf* shelf){
    char str[100000] = "92104898120951924098142";
    int sizeNA = 10, iNA=0, size = 10, numOfShlvs = 0, serie = 0, check = 0;
    finalProd* result = (finalProd*)malloc(size * (sizeof(*result)));
    char** notAvalaible = (char**)malloc(sizeNA * sizeof(*notAvalaible));
    while(1){
        fgets(str, 100000, stdin);
        check++;
        if(!strcmp(str, "92104898120951924098142")){
            free(result);
            free(notAvalaible);
            return 0;
        }
        if(feof(stdin)){
            if(str[strlen(str)-1] != '\n'){
                if(findProdSame(shelf, str, -1, &result,  &size, &numOfShlvs)){
                    if(findProdSub(shelf, str, -1, &result,  &size, &numOfShlvs)){
                        notAvalaible[iNA] = (char*)malloc((strlen(str)+1)*sizeof(char));
                        strcpy(notAvalaible[iNA++], str); 
                        if(iNA == sizeNA){
                            sizeNA*=2;
                            notAvalaible = (char**)realloc( notAvalaible,sizeNA*sizeof(char*));
                        }
                    }
                    else serie++;
                }else serie++;
            }
            qsort( (void*)result, numOfShlvs, sizeof(result[0]), ( int(*)(const void *, const void *) ) shlvCompare );
            printf("Optimalizovany seznam:\n");
            printRes(result, numOfShlvs);
            printNA(notAvalaible,iNA, serie);
            for(int i = 0; i < iNA; i++) free(notAvalaible[i]);
            free(notAvalaible);
            cleanArr(result, numOfShlvs);
            return 0;
        }
        if(str[0] == '\n'){
            qsort( (void*)result, numOfShlvs, sizeof(result[0]), ( int(*)(const void *, const void *) ) shlvCompare );
            printf("Optimalizovany seznam:\n");
            printRes(result, numOfShlvs);
            printNA(notAvalaible,iNA, serie);
            for(int i = 0; i < iNA; i++) free(notAvalaible[i]);
            free(notAvalaible);
            cleanArr(result, numOfShlvs);
            searching(shelf);
            return 0;
        }
        str[strlen(str)-1] = '\0';
        if(findProdSame(shelf, str, -1, &result,  &size, &numOfShlvs)){
            if(findProdSub(shelf, str, -1, &result,  &size, &numOfShlvs)){
                notAvalaible[iNA] = (char*)malloc((strlen(str)+1)*sizeof(char));
                strcpy(notAvalaible[iNA++], str);
                if(iNA == sizeNA){
                    sizeNA*=2;
                    notAvalaible = (char**)realloc(notAvalaible,sizeNA*sizeof(char*));
                } 
            }
            else serie++;
        }else serie++;
        str[strlen(str)-1] = '\n';
    }
}


int main(){
    Shelf* head = NULL;
    int number = 0;
    if(input(&head, &number)) {
        clean(head);
        return 1;
    }
    searching(head);
    // print(head);
    clean(head);
    return 0;
}