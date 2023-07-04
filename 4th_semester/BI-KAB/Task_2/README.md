# Task description
    Your task is to implement two (or more) functions (not the whole program) that can encrypt and decrypt an image file in TGA format.

    For our task, we will consider a simplified form of the image:

    Mandatory header: 18 bytes - we do not modify these bytes in any way, we just copy them into the encrypted image.
    Optional header part: the size is calculated from the mandatory header part - we will consider this part of the header as image data, i.e. we will encrypt it together with the image data without modification.
    Image data: the rest.
    The parameters of the functions you implemented are:

    bool encrypt_data (const string & in_filename, const string & out_filename, crypto_config & config)
    in_filename - input filename,
    out_filename - output filename,
    config - the crypto_config data structure described below.
    The return value is true on success, false otherwise. Failure occurs if the file is invalid in some way (missing mandatory header, fails to open, read, write, ...) or fails to fix invalid crypto_config configuration.
    The decrypt_data function uses the same interface, but performs the inverse operation with respect to encryption. It copies the mandatory part of the header that is not encrypted, then decrypts the rest of the file in the same way as the encryption. In this case, however, we expect to pass a valid decryption key and IV (if needed). If we don't have these parameters, we can't decrypt the data and the program should report an error (return false).

    The crypto_config data structure contains:

    the selected block cipher specified by its name,
    the secret encryption key and its size,
    the initialization vector (IV) and its size.
    The following problem may occur during encryption: if the encryption key (or IV) is insufficient (i.e., their length is not at least as large as required by the chosen block cipher or is missing altogether), they must be generated securely. If the specified block cipher does not need an IV (and thus does not need to be passed to you), do not generate a new IV! Remember to store the generated keys and IVs in the transmitted config structure if necessary!

    You will find the following encryption functions useful:

    EVP_EncryptInit_ex and EVP_DecryptInit_ex,
    EVP_EncryptUpdate and EVP_DecryptUpdate,
    EVP_EncryptFinal_ex and EVP_DecryptFinal_ex respectively.
    See the openssl documentation to see what other features you could (and should) use. Hint: Isn't there a more general function that covers these functions?

    By default, block ciphers have padding enabled, so the length of the resulting encrypted file may be longer than the original. This is the desired (and in tests expected behavior) and should not be changed.

    In a test environment you will be limited not only by time but also by the size of the available memory, your program may eventually be forcibly terminated. Therefore, try not to use the heap unnecessarily or ideally do not use it at all. In 90% of cases you will be fine with just the heap.

    Commit a source file that contains the implementation of the requested encrypt_data and decrypt_data functions. You can also add your other support functions that are called from encrypt_data and decrypt_data to the source file. The function will be called from the test environment, so it is important to follow the specified function interface exactly.

    Use the code from the attached archive below as a basis for implementation. The sample contains the main test function, the values given are used in the basic test. Note that the header file insertion and the main function are wrapped in a conditional compilation block (#ifdef/#endif). Please leave the conditional translation blocks in the committed source file as well. Conditional translation will simplify your work. When compiled on your machine, you can run and test the program normally. When compiling on Progtest, the main function and the header file insertion "disappear", i.e. they will not interfere with the header files and the main function of the test environment.