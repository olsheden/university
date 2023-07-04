#ifndef __PROGTEST__
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <unistd.h>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <cassert>
#include <cstring>

#include <openssl/evp.h>
#include <openssl/rand.h>

using namespace std;

struct crypto_config
{
	const char * m_crypto_function;
	std::unique_ptr<uint8_t[]> m_key;
	std::unique_ptr<uint8_t[]> m_IV;
	size_t m_key_len;
	size_t m_IV_len;
};

#endif /* _PROGTEST_ */

bool fixConfig(crypto_config& config, const EVP_CIPHER* cipher, bool x)
{
    size_t k_len = static_cast<size_t>(EVP_CIPHER_key_length(cipher));
    size_t iv_len = static_cast<size_t>(EVP_CIPHER_iv_length(cipher));
    if (!config.m_key || (config.m_key_len < k_len))
    {
        if(x){
            config.m_key = std::make_unique<uint8_t[]>(k_len);
            if (RAND_bytes(config.m_key.get(), k_len) != 1)
            {
                return false;
            }
            config.m_key_len = k_len;
        }
        else return false;
    }
    if ((!config.m_IV || iv_len > config.m_IV_len) && iv_len > 0)
    {
        if(x){
            config.m_IV = std::make_unique<uint8_t[]>(iv_len);
            if (RAND_bytes(config.m_IV.get(), iv_len) != 1)
            {
                return false;
            }
            config.m_IV_len = iv_len;
        }
        else return false;
    }
    return true;
}


bool encrypt_data(const std::string& in_filename, const std::string& out_filename, crypto_config& config)
{
    std::ifstream in_file(in_filename, std::ios::binary);
    if (!in_file.is_open())
    {
        return false;
    }

    std::ofstream out_file(out_filename, std::ios::binary);
    if (!out_file.is_open())
    {
        in_file.close();
        return false;
    }
    char header[18];
    if (!in_file.read(header, sizeof(header)) || !in_file.good())
    {
        in_file.close();
        out_file.close();
        return false;
    }

    out_file.write(header, sizeof(header));
    if(!out_file.good()){
        in_file.close();
        out_file.close();
        return false;
    }

    if(!config.m_crypto_function){
        in_file.close();
        out_file.close();
        return false;
    }
    const EVP_CIPHER *cipher = EVP_get_cipherbyname(config.m_crypto_function);
    if (!cipher)
    {
        in_file.close();
        out_file.close();
        return false;
    }
    if(!fixConfig(config, cipher, true)){
        in_file.close();
        out_file.close();
        return false;
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
    {
        in_file.close();
        out_file.close();
        return false;
    }
    
    if (!EVP_EncryptInit_ex(ctx, cipher, NULL, config.m_key.get(), config.m_IV.get()))
    {
        EVP_CIPHER_CTX_free(ctx);
        in_file.close();
        out_file.close();
        return false;
    }

    const size_t input_size = 4096; 
    uint8_t in_buffer[4096];
    uint8_t out_buffer[4096 + EVP_MAX_BLOCK_LENGTH];

    while (true) 
    {
        int in_len = in_file.read(reinterpret_cast<char *>(in_buffer), input_size).gcount();
        if (in_len <= 0) 
        {
            break;
        }

        int out_len;
        if (EVP_EncryptUpdate(ctx, out_buffer, &out_len, in_buffer, in_len) != 1)
        {
            EVP_CIPHER_CTX_free(ctx);
            in_file.close();
            out_file.close();
            return false;
        }

        out_file.write(reinterpret_cast<const char *>(out_buffer), out_len);
        if (!out_file.good()) {
            EVP_CIPHER_CTX_free(ctx);
            in_file.close();
            out_file.close();
            return false;
        }
    }
    
    int out_len;
    if (EVP_EncryptFinal_ex(ctx, out_buffer, &out_len) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        in_file.close();
        out_file.close();
        return false;
    }

    out_file.write(reinterpret_cast<const char *>(out_buffer), out_len);
    if (!out_file.good()) {
        EVP_CIPHER_CTX_free(ctx);
        in_file.close();
        out_file.close();
        return false;
    }
    EVP_CIPHER_CTX_free(ctx);
    in_file.close();
    out_file.close();
    return true;
}

bool decrypt_data(const std::string& in_filename, const std::string& out_filename, crypto_config& config)
{
    std::ifstream in_file(in_filename, std::ios::binary);
    if (!in_file.is_open())
    {
        return false;
    }

    std::ofstream out_file(out_filename, std::ios::binary);
    if (!out_file.is_open())
    {
        in_file.close();
        return false;
    }

    char header[18];
    if (!in_file.read(header, sizeof(header)) || !in_file.good())
    {
        in_file.close();
        out_file.close();
        return false;
    }

    out_file.write(header, sizeof(header));
    if(!out_file.good()){
        in_file.close();
        out_file.close();
        return false;
    }

    if(!config.m_crypto_function){
        in_file.close();
        out_file.close();
        return false;
    }
    const EVP_CIPHER *cipher = EVP_get_cipherbyname(config.m_crypto_function);
    if (!cipher)
    {
        in_file.close();
        out_file.close();
        return false;
    }

    if(!fixConfig(config, cipher, false)) {
        in_file.close();
        out_file.close();
        return false;
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
    {
        in_file.close();
        out_file.close();
        return false;
    }

    if (!EVP_DecryptInit_ex(ctx, cipher, NULL, config.m_key.get(), config.m_IV.get()))
    {
        EVP_CIPHER_CTX_free(ctx);
        in_file.close();
        out_file.close();
        return false;
    }

    const size_t input_size = 4096; 
    uint8_t in_buffer[4096];
    uint8_t out_buffer[4096 + EVP_MAX_BLOCK_LENGTH];

    while (true) 
    {
        int in_len = in_file.read(reinterpret_cast<char *>(in_buffer), input_size).gcount();
        if (in_len <= 0) 
        {
            break;
        }

        int out_len;
        if (EVP_DecryptUpdate(ctx, out_buffer, &out_len, in_buffer, in_len) != 1)
        {
            EVP_CIPHER_CTX_free(ctx);
            in_file.close();
            out_file.close();
            return false;
        }

        out_file.write(reinterpret_cast<const char *>(out_buffer), out_len);
        if (!out_file.good()) {
            EVP_CIPHER_CTX_free(ctx);
            in_file.close();
            out_file.close();
            return false;
        }
    }
    
    int out_len;
    if (EVP_DecryptFinal_ex(ctx, out_buffer, &out_len) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        in_file.close();
        out_file.close();
        return false;
    }

    out_file.write(reinterpret_cast<const char *>(out_buffer), out_len);
    if (!out_file.good()) {
        EVP_CIPHER_CTX_free(ctx);
        in_file.close();
        out_file.close();
        return false;
    }
    EVP_CIPHER_CTX_free(ctx);
    in_file.close();
    out_file.close();
    return true;
}


#ifndef __PROGTEST__



int main ( void )
{
	crypto_config config {nullptr, nullptr, nullptr, 0, 0};

	// ECB mode
	config.m_crypto_function = "AES-128-ECB";
	config.m_key = std::make_unique<uint8_t[]>(16);
 	memset(config.m_key.get(), 0, 16);
	config.m_key_len = 16;

	assert( encrypt_data  ("homer-simpson.TGA", "out_file.TGA", config) &&
			compare_files ("out_file.TGA", "homer-simpson_enc_ecb.TGA") );

	assert( decrypt_data  ("homer-simpson_enc_ecb.TGA", "out_file.TGA", config) &&
			compare_files ("out_file.TGA", "homer-simpson.TGA") );

	assert( encrypt_data  ("UCM8.TGA", "out_file.TGA", config) &&
			compare_files ("out_file.TGA", "UCM8_enc_ecb.TGA") );

	assert( decrypt_data  ("UCM8_enc_ecb.TGA", "out_file.TGA", config) &&
			compare_files ("out_file.TGA", "UCM8.TGA") );

	assert( encrypt_data  ("image_1.TGA", "out_file.TGA", config) &&
			compare_files ("out_file.TGA", "ref_1_enc_ecb.TGA") );

	assert( encrypt_data  ("image_2.TGA", "out_file.TGA", config) &&
			compare_files ("out_file.TGA", "ref_2_enc_ecb.TGA") );

	assert( decrypt_data ("image_3_enc_ecb.TGA", "out_file.TGA", config)  &&
		    compare_files("out_file.TGA", "ref_3_dec_ecb.TGA") );

	assert( decrypt_data ("image_4_enc_ecb.TGA", "out_file.TGA", config)  &&
		    compare_files("out_file.TGA", "ref_4_dec_ecb.TGA") );

	// CBC mode
	config.m_crypto_function = "AES-128-CBC";
	config.m_IV = std::make_unique<uint8_t[]>(16);
	config.m_IV_len = 16;
	memset(config.m_IV.get(), 0, 16);

	assert( encrypt_data  ("UCM8.TGA", "out_file.TGA", config) &&
			compare_files ("out_file.TGA", "UCM8_enc_cbc.TGA") );

	assert( decrypt_data  ("UCM8_enc_cbc.TGA", "out_file.TGA", config) &&
			compare_files ("out_file.TGA", "UCM8.TGA") );

	assert( encrypt_data  ("homer-simpson.TGA", "out_file.TGA", config) &&
			compare_files ("out_file.TGA", "homer-simpson_enc_cbc.TGA") );

	assert( decrypt_data  ("homer-simpson_enc_cbc.TGA", "out_file.TGA", config) &&
			compare_files ("out_file.TGA", "homer-simpson.TGA") );

	assert( encrypt_data  ("image_1.TGA", "out_file.TGA", config) &&
			compare_files ("out_file.TGA", "ref_5_enc_cbc.TGA") );

	assert( encrypt_data  ("image_2.TGA", "out_file.TGA", config) &&
			compare_files ("out_file.TGA", "ref_6_enc_cbc.TGA") );

	assert( decrypt_data ("image_7_enc_cbc.TGA", "out_file.TGA", config)  &&
		    compare_files("out_file.TGA", "ref_7_dec_cbc.TGA") );

	assert( decrypt_data ("image_8_enc_cbc.TGA", "out_file.TGA", config)  &&
		    compare_files("out_file.TGA", "ref_8_dec_cbc.TGA") );
	return 0;
}

#endif /* _PROGTEST_ */
