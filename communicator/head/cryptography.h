#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <cryptopp/sha.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/rijndael.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/filters.h>
#include <cryptopp/aes.h>
#include <cryptopp/gcm.h>
#include <cryptopp/osrng.h>
#include <iostream>
// DH
#include <cryptopp/dh.h>
#include <cryptopp/integer.h>
#include <stdexcept>
#include <sstream>


/**
  This function calculates SHA256
  @param _prehash hash function input
  @return 32 byte array
*/
const byte* CalcSHA256( const std::string _prehash);

/**
  This function converts 32 byte array to std::string
  @param _input 32 byte array
  @return std::string of 32 byte array
*/
const std::string b32byteToString( const byte* _input );

/**
  This function converts  std::string  to 32 byte array
  @param _input 32 std::string
  @return 32 byte array
*/
const byte* b32StringToByte( const std::string _input);

/**
  This function encrypts std::string using AES-256
  @param _key encryption key of 32 byte length
  @param _iv  16 byte long initialization vector
  @param _input std::string to be b32AESEncrypted
  @return encrypted std::string
*/
const std::string b32AESEncrypted(const byte* _key, const byte* _iv, const std::string _input);

/**
  This function decrypts std::string using AES-256
  @param _key decryption key of 32 byte length
  @param _iv  16 byte long initialization vector
  @param _input std::string to be b32AESEncrypted
  @return encrypted std::string
*/
const std::string b32AESDecrypted(const byte* _key, const byte* _iv, const std::string _input);

/**
   CryptoPP::Integer to std::string converter
 * @brief IntegerTostring
 * @param _int
 * @return std::string
 */
const std::string IntegerTostring(const CryptoPP::Integer _int);
#endif // CRYPTOGRAPHY_H

