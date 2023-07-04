#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TItem
{
    struct TItem             * m_Next;
    char                     * m_Name;
    char                       m_Secret[24];
} TITEM;

int cmpName ( const TITEM * a,
              const TITEM * b )
{
    return strcmp ( a -> m_Name, b -> m_Name );
}

int cmpNameInsensitive ( const TITEM * a,
                         const TITEM * b )
{
    return strcasecmp ( a -> m_Name, b -> m_Name );
}

int cmpNameLen ( const TITEM * a,
                 const TITEM * b )
{
    size_t la = strlen ( a -> m_Name ), lb = strlen ( b -> m_Name );
    return ( lb < la ) - ( la < lb );
}
#endif /* __PROGTEST__ */

TITEM            * newItem      ( const char      * name,
                                  TITEM           * next )
{
    TITEM* tmp = (TITEM*)malloc(sizeof(TITEM));
    tmp->m_Name = (char*)malloc((strlen(name) + 1)*sizeof(char));
    strcpy(tmp->m_Name, name);
    tmp->m_Next = next;
    return tmp;
}

void split(TITEM* head, TITEM** firstword, TITEM** secondword, int length){
    (*firstword) = head;
    for(int i = 1; i < (int)(length/2) ; i++){
        (*firstword) = (*firstword)->m_Next;
    }
    (*secondword) = (*firstword)->m_Next;
    (*firstword)->m_Next = NULL;
    (*firstword) = head;
}

void merge(TITEM* firstword, TITEM* secondword, TITEM** tmp, int            (* cmpFn) ( const TITEM *, const TITEM *)){

    if(!firstword) {
        (*tmp) = secondword;
        return ;
    }
    else if(!secondword) {
        (*tmp) = firstword;
        return;
    }

    if(cmpFn(firstword, secondword) <= 0){
        (*tmp) = firstword;
        merge(firstword->m_Next, secondword, &(*tmp)->m_Next, cmpFn);
    }
    else{
        (*tmp) = secondword;
        merge(firstword, secondword->m_Next, &(*tmp)->m_Next, cmpFn);
    }

    return;
}

void merge2(TITEM* firstword, TITEM* secondword, TITEM** tmp, int            (* cmpFn) ( const TITEM *, const TITEM *)){

    if(!firstword) {
        (*tmp) = secondword;
        return ;
    }
    else if(!secondword) {
        (*tmp) = firstword;
        return;
    }

    if(cmpFn(firstword, secondword) >= 0){
        (*tmp) = firstword;
        merge2(firstword->m_Next, secondword, &(*tmp)->m_Next, cmpFn);
    }
    else{
        (*tmp) = secondword;
        merge2(firstword, secondword->m_Next, &(*tmp)->m_Next, cmpFn);
    }

    return;
}

void mergesort(TITEM** l, int x, int            (* cmpFn) ( const TITEM *, const TITEM *)){
    TITEM* head = (*l);
    TITEM* firstword;
    TITEM* secondword;
    int length = 0;
    while(head){
        head = head->m_Next;
        length++;
    }
    head = (*l);
    if(length <= 1) return ;
    split(head, &firstword, &secondword, length);
    mergesort(&firstword, x, cmpFn);
    mergesort(&secondword, x, cmpFn);
    TITEM* tmp;
    if(x == 1) {
        merge(firstword, secondword, &tmp, cmpFn);
        (*l) = tmp;
    }
    else if(x == 0) {
        merge2(firstword, secondword, &tmp, cmpFn);
        (*l) = tmp;
    }
}

TITEM            * sortListCmp  ( TITEM           * l,
                                  int               ascending,
                                  int            (* cmpFn) ( const TITEM *, const TITEM *) )
{
    if(ascending){
        mergesort(&l, 1, cmpFn);
    }
    else{
        mergesort(&l, 0, cmpFn);
    }
    return l;
}


void               freeList     ( TITEM           * src )
{
    while(src){
        TITEM*  tmp = src->m_Next;
        free(src->m_Name);
        free(src);
        src = tmp;
    }
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
        return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
