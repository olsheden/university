# Task description
    The task is to implement a set of functions (not the whole program, just functions) for working with linked lists. The functions will allow the list to be easily created, deleted and sorted. The task is an extension of the simpler assignment, adding the possibility of a custom comparator. We recommend to solve the simpler assignment first and then extend it.


    When solving the problem, you will encounter the following declarations:


    TITEM
    This structure represents an element of a unidirectionally concatenated linked list. The declaration of the structure is fixed in the test environment, your implementation will use this unchanged declaration (it cannot/must not change it). The structure contains the following components:
    m_Next pointer to the next element in the linked list, NULL value for the last element,
    m_Name a string with the name of the list element,
    m_Secret the secret data associated with this list item. Your implementation does not need to work with this component and must not change it (the exception is initialization in the newItem function).
    TITEM * newItem ( const char * name, TITEM * next )
    This function creates a new TITEM entry. You will allocate memory for the structure dynamically. In addition, the function will copy the name and reference to the next item from the parameters into the m_Next and m_Name folders. The m_Secret folder will be filled with null bytes ('\0'). The return value of the function is a pointer to the TITEM structure thus created and initialized. The implementation of the function is your task.
    void freeList ( TITEM * l )
    This function is used to conveniently delete a linked list. The parameter is the start of the deleted linked list l. The function will free all the resources that the list occupied. The implementation of the function is your responsibility.
    TITEM * sortListCmp ( TITEM * l, int ascending, int (*cmp)(const TITEM *, const TITEM *) )
    This function is used to sort the elements in a linked list. The parameters are the start of the sorted linked list l, the desired ascending ordering, and the comparator cmp. The function will rearrange the elements in the specified list so that the order matches the desired ordering. The function must not release the elements of the original list (and, for example, return a newly created copy of them). On the contrary, it must reconnect the references of the existing elements and return a pointer to the first element of the resulting list.


    The sorting criterion is the result after calling the cmp comparator. Whenever it is necessary to determine the relative ordering of two elements, the sorting algorithm calls the function passed by the cmp parameter Calling the comparator works the same way as in the library function qsort - it returns a negative / zero / positive value if the first parameter passed to the comparator was smaller / equal / larger than the second parameter. The ordering further affects the direction of the ordering - it is either ascending (the ascending parameter is non-zero) or descending (the ascending parameter is zero). The function must ensure that the ordering is stable.


    Submit a source file that contains an implementation of the required functions. Add to the source file your other supporting functions that are called from the implemented functions. The functions will be called from the test environment, so it is important to follow the specified function interface exactly. Use the code from the attached archive as the basis for the implementation. The sample contains the test function main, the values given are used in the basic test. Note that the header file insertion and the main function are wrapped in a conditional compilation block (#ifdef/#endif). Please leave the conditional translation blocks in the committed source file as well. Conditional translation will simplify your work. When compiled on your machine, you can run and test the program normally. When compiling on Progtest, the main function and the header file insertion "disappear", i.e. they will not interfere with the header files and the main function of the test environment.