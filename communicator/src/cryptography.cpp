#include "../head/cryptography.h"


const byte* CalcSHA256( const std::string _prehash){
  CryptoPP::SHA256 hash;
  byte* digest = new byte[ CryptoPP::SHA256::DIGESTSIZE ];
  hash.CalculateDigest( digest, (byte*) _prehash.c_str(), _prehash.length() );
  return digest;
}

const std::string b32byteToString( const byte* _input ){
  std::string output;
  CryptoPP::HexEncoder encoder;
  encoder.Attach( new CryptoPP::StringSink( output ) );
  encoder.Put( _input, CryptoPP::SHA256::DIGESTSIZE );
  encoder.MessageEnd();
  return output;
}

const byte* b32StringToByte( const std::string _input){
 std::string destination;
 CryptoPP::StringSource ss(_input, true, new CryptoPP::HexDecoder(new CryptoPP::StringSink(destination)));
 byte* newDigest = new byte[ CryptoPP::SHA256::DIGESTSIZE ];
 for(int i=0; i<destination.size(); i++)
    newDigest[i] = (byte) destination[i];

 return newDigest;
}

const std::string b32AESEncrypted(const byte* _key, const byte* _iv, const std::string _input)
{
  try{
    // key
    CryptoPP::AES::Encryption aesEncryption(_key, CryptoPP::AES::MAX_KEYLENGTH);
    // iv
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, _iv );

    std::string encrypted;
    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( encrypted ) );
    stfEncryptor.Put( reinterpret_cast<const unsigned char*>( _input.c_str() ), _input.length() );
    stfEncryptor.MessageEnd();
    return encrypted;

  }catch(std::exception &e){
    std::cerr << "Error at encryption: " << e.what() << std::endl;
    return "";
  }
  return "";
}

const std::string b32AESDecrypted(const byte* _key, const byte* _iv, const std::string _input)
{
  try{
    CryptoPP::AES::Decryption aesDecryption(_key, CryptoPP::AES::MAX_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, _iv );
    std::string decrypted;
    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decrypted ) );
    stfDecryptor.Put( reinterpret_cast<const unsigned char*>( _input.c_str() ), _input.size() );
    stfDecryptor.MessageEnd();
    return decrypted;
  }catch( std::exception &e ){
    std::cerr << "Error at decryption: " << e.what() << std::endl;
    return "";
  }
  return "";
}

const std::string IntegerTostring(const CryptoPP::Integer _int){
    std::stringstream temp;
    temp << std::hex << _int;
    return temp.str();
}
