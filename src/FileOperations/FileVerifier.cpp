#include "FileVerifier.h"
int FileVerifier::getVerificationKeyForFile(const std::string & fileContent){
    return getHash(fileContent) + KEY;
}

bool FileVerifier::verifyFile(const std::string fileContent, const int verificationKey){
    return (getHash(fileContent) == verificationKey - KEY);
}

int FileVerifier::getHash(const std::string& str){
    std::size_t hash = 14695981039346656037ull;
    for (char c : str)
    {
        hash ^= static_cast<std::size_t>(c);
        hash *= 1099511628211ull;
    }
   return ((int) abs(hash % 10000000));
}