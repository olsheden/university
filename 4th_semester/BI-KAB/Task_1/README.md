# Task description
    Your task is to implement a function (or set of functions, not the whole program) that finds any message whose hash (SHA-512) starts from the left on a sequence of zero bits.

    The bit order is big-endian: Byte 0 from MSB to LSB, Byte 1 from MSB to LSB, ..., last byte from MSB to LSB.

    Or, the two zero bits correspond, for example, to byte 0010 0111 (0x27).

    The function is requested in two variants:

    basic solution (findHash function). Implementation of this function is mandatory.
    Enhanced solution (function findHashEx). The implementation of this function is not mandatory, but without the supplied "dummy" implementation the task fails to compile. Implement the function if you decide to pursue the bonus.
    The parameters of the functions you implement are:

    int findHash (int bits, char ** message, char ** hash)
    bits - the desired number of null bits in the message hash.
    message - output parameter. This parameter contains the data for which the corresponding hash was found. The result is stored as a dynamically allocated hexadecimal C string (terminated by \0).
    hash - output parameter. This is the message hash of the message from the previous parameter, again it is a hexadecimal C string dynamically allocated by you.
    The return value of the function is 1 in case of success, 0 in case of failure or incorrect parameters. These are typically the required number of null bits, which makes no sense.
    int findHashEx (int bits, char ** message, char ** hash, const char * hashFunction)
    Extension of the findHash function. All parameters and the return value remain the same as in the basic variant.
    hashFunction - new parameter that specifies which hash function should be used to find a sequence of null bits. The specified hash function name is compatible with the EVP_get_digestbyname function.
    You do not need to worry about releasing the dynamically allocated counter resources (message and hash; but only if the function succeeds), the test environment will ensure that they are released correctly. However, all other memory work is up to you.

    Commit a source file that contains the implementation of the requested findHash or findHashEx function. You can also add your other support functions that are called from findHash (or findHashEx) to the source file. The function will be called from the test environment, so it is important to follow the specified function interface exactly.

    Use the code from the attached archive below as a basis for implementation. The sample contains the test function main, the values given are used in the basic test. Note that the header file insertion and the main function are wrapped in a conditional compilation block (#ifdef/#endif). Please leave the conditional translation blocks in the committed source file as well. Conditional translation will simplify your work. When compiled on your machine, you can run and test the program normally. When compiling on Progtest, the main function and the header file insertion "disappear", i.e. they will not interfere with the header files and the main function of the test environment.

    The sample also includes the checkHash function, which you will (in all likelihood) have to implement for your local testing. The function is wrapped in a conditional compilation block (=will not be tested). Still, it is advisable to implement it to verify the correctness of your solution.