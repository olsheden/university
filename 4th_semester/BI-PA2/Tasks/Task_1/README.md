# Task description
    The task is to create C/C++ functions that can transcode a file in UTF8 encoding to Fibonacci code and back.

    We store the characters as numbers - indices in a code table, nowadays mostly UNICODE. There are many characters in UNICODE - 1048576+65536. If they were stored directly as binary numbers, 4 bytes would always be needed to represent one character. However, most characters have lower codes, e.g. values less than 128 (65536). This is exploited by UTF-8 encoding, which stores the character more compactly in 1 to 4 bytes, depending on the value being written.

    UTF-8 encoding for regular text files reduces the overall volume of data stored, but is not optimal. In designing UTF-8 encoding, a method was chosen where the character codes always end on a full byte boundary. This is practical for fast retrieval, but it is not optimal in terms of length.

    Other codes have been developed for memory-efficient storage of integers, such as the Fibonacci code, which is based on the Fibonacci sequence. Recall that a Fibonacci sequence is a sequence of integers where each successive number in the sequence is formed as the sum of the two previous numbers. The sequence takes the form 1, 1, 2, 3, 5, 8, ... The numbers in the Fibonacci code are stored as bit sequences that use a set bit to indicate the presence of the corresponding element of the Fibonacci sequence. For example, the number 9 can be written as:

                                1 1 2 3 5 8 ....
    9 = 1 + 8 1 0 0 0 0 1
    9 = 1 + 8 0 1 0 0 0 1
    9 = 1 + 3 + 5 1 0 0 1 1
    9 = 1 + 1 + 2 + 5 1 1 1 0 1 
    ...
    There are many possible notations. From all variants, only those notations are selected where no number in the Fibonacci sequence is repeated more than once (i.e. the notation 1 + 1 + 2 + 5 will not be used). Because of this restriction, we do not need to consider two initial ones in the Fibonacci sequence, only one of them could be used anyway. Furthermore, we will not allow entries where adjacent members of the Fibonacci sequence occur (thus the entry 1 + 3 + 5 will also be inadmissible, 3 and 5 are neighbours). A pair of adjacent elements of a Fibonacci sequence can always be replaced by their sum, i.e. by the next element in the sequence.

    With these restrictions, the Fibonacci code is already unambiguous. For the first few integers it takes the form:

                                1 2 3 5 8 
    1 = 1 1
    2 = 2 0 1
    3 = 3 0 0 1
    4 = 1 + 3 1 0 1
    5 = 5 0 0 0 1
    6 = 1 + 5 1 0 0 1
    7 = 2 + 5 0 1 0 1
    8 = 8 0 0 0 0 1
    9 = 1 + 8 1 0 0 0 1
    10 = 2 + 8 0 1 0 0 1
    11 = 3 + 8 0 0 1 0 1
    12 = 1 + 3 + 8 1 0 1 0 1
    ...
    So integers can be stored using Fibonacci code. Note that small numbers are encoded with shorter bit sequences, large numbers with longer sequences. The problem, however, is recognizing where one number's code ends and the next number's code begins. For binary notation with a fixed number of bits, this is trivial - we divide the bit sequences into groups of 8/16/32/64 bits according to the fixed size of the data type. But here we would like to use a variable number of bits to save space. Let's imagine a situation where the input is a sequence of 00101 bits. This can be thought of as a single number (11) or as two numbers 3 and 2 if we split the bit sequence into groups 001 01.

    To mark the end of the number, we need to add an agreed marker to the sequence. For the Fibonacci sequence this is easy, we add one bit with the value 1 between the numbers. Since the code always ends with a one, adding another one gives us a sequence of two unit bits. Due to the properties of the Fibonacci code, such a sequence cannot occur in the middle of the coded number, so it will uniquely identify the end of the code. Thus, the number 11 itself from the example would be coded as the sequence 001011, and the sequence of two numbers 3 and 2 would be coded as 0011011.

    The Fibonacci code cannot store a value of 0 in this embodiment. This is handled simply by shifting the entire code by 1 position:

                                1 2 3 5 8 
    0 ~ 1 1 1
    1 ~ 2 0 1 1
    2 ~ 3 0 0 1 1
    3 ~ 1 + 3 1 0 1 1
    4 ~ 5 0 0 0 1 1
    5 ~ 1 + 5 1 0 0 1 1
    6 ~ 2 + 5 0 1 0 1 1
    7 ~ 8 0 0 0 0 1 1
    8 ~ 1 + 8 1 0 0 0 1 1
    9 ~ 2 + 8 0 1 0 0 1 1
    10 ~ 3 + 8 0 0 1 0 1 1
    11 ~ 1 + 3 + 8 1 0 1 0 1 1
    ...

    The last problem is alignment. If we are to encode, for example, a sequence of numbers 0 5 10, then we need to store a total of 2 + 5 + 6 = 13 bits. We are able to store integer bytes in the file, so we set the unused bits (max 7 at the end of the file) to zero. Because this padding does not contain a sequence of two consecutive ones, this padding cannot inadvertently add another encoded character.

    Example of encoding a sequence of characters with values 0 5 10:

    Character codes: 0 5 10 
    Bit sequence: 11 10011 001011
    Grouping: 1110011001011 
    Completion to whole bytes: 1110011001011000 
    Bytes (LSB left): 11100110 01011000
    Bytes (LSB right): 01100111 00011010  
    Bytes hexadecimal: 67 1A
    Note: LSB stands for Least Significant Bit. When explaining the codes I considered writing with LSB on the left, the codes are more illustrative. However, when writing bytes and in hexdump, we work with LSB on the right. For implementation, just choose the conventional approach (LSB right) and subordinate the bit-to-byte folding to that. The notation with LSB left should be understood only as an aid for easier understanding.

    The challenge is to implement the two functions with the interface below. Both functions have two file names as parameters: source and destination. The functions read the source file and write the transcoded result to the destination file. The return value of both functions is a success (true) or error (false) flag. If anything fails during the requested operation (open file / create file / read source / write target / incorrect data format / ...), the function will return false.