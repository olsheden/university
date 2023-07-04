#ifndef __PROGTEST__
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <openssl/evp.h>
#include <openssl/rand.h>

#endif /* __PROGTEST__ */

void change(unsigned char *tmp_msg) {
    for (int i = 0; i < 4; i++) {
        int index = rand() % 13;
        unsigned char shift = rand() % 8;
        tmp_msg[index] = (tmp_msg[index] << shift) | (tmp_msg[index] >> (8 - shift));
    }
}

int findHash(int bits, char **message, char **hash) {
    EVP_MD_CTX *ctx;
    const EVP_MD *type;
    size_t i;
    
    if (bits < 0 || bits > 512) {
        return 0;
    }


    type = EVP_get_digestbyname("SHA512");

    bool flag;
    unsigned char* tmp_hash = (unsigned char*)malloc(65);
    unsigned char* tmp_msg = (unsigned char*)malloc(14);
    tmp_hash[64] = '\0';

    if (!RAND_bytes( tmp_msg, 13)) {
        free(tmp_hash);
        free(tmp_msg);
        return 0;
    }
    tmp_msg[13] = '\0';

    while (true) {

        ctx = EVP_MD_CTX_new();
        if (ctx == NULL) {
            free(tmp_hash);
            free(tmp_msg);
            return 0;
        }

        if (!EVP_DigestInit_ex(ctx, type, NULL)) {
            EVP_MD_CTX_free(ctx);
            free(tmp_hash);
            free(tmp_msg);
            return 0;
        }

        if (!EVP_DigestUpdate(ctx, tmp_msg, 13)) {
            EVP_MD_CTX_free(ctx);
            free(tmp_hash);
            free(tmp_msg);
            return 0;
        }

        if (!EVP_DigestFinal_ex(ctx, tmp_hash, NULL)) {
            EVP_MD_CTX_free(ctx);
            free(tmp_hash);
            free(tmp_msg);
            return 0;
        }

        EVP_MD_CTX_free(ctx);

        flag = true;

        for(int i = 0; i < bits; i++){
            int byte = i/8;
            int shift = (7 - (i % 8));
            if (((tmp_hash[byte] >> shift) == 1)){
                flag = false;
                break;
            }
        }
        if(!flag){
            change((unsigned char*)tmp_msg);
            continue;
        } 
        else break;
        }
    
    char *hex_message = (char *) malloc(27);
    char *hex_hash = (char *) malloc(129);
    for (i = 0; i < 13; ++i) {
        snprintf(hex_message + 2 * i, 3, "%02X", tmp_msg[i] & 0xff);
    }
    hex_message[26] = '\0';
    for (i = 0; i < 64; ++i) {
        snprintf(hex_hash + 2 * i, 3, "%02X", tmp_hash[i] & 0xff);
    }
    hex_hash[128] = '\0';

    *message = hex_message;
    *hash = hex_hash;
    free(tmp_hash);
    free(tmp_msg);
    return 1;
}


int findHashEx (int bits, char ** message, char ** hash, const char * hashFunction) {
    if (!strcmp(hashFunction, "SHA512") ) {
        return findHash(bits, message, hash);
    } else {
        return 0;
    }
}

#ifndef __PROGTEST__

int checkHash (int bits, const char * hash)
{
    for(int i = 0; i < bits; i++){
        int shift = (7 - (i % 8));
        int byte = i/8;
        if (((hash[byte] >> shift) == 1)){
            return 0;
        }
    }

 return 1;
}


int main (void) {
    char * message, * hash;
    assert(findHash(0, &message, &hash) == 1);
    assert(message && hash && checkHash(0, hash));
    free(message);
    free(hash);
    assert(findHash(1, &message, &hash) == 1);
    assert(message && hash && checkHash(1, hash));
    free(message);
    free(hash);
    assert(findHash(2, &message, &hash) == 1);
    assert(message && hash && checkHash(2, hash));
    free(message);
    free(hash);
    assert(findHash(-1, &message, &hash) == 0);
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */

