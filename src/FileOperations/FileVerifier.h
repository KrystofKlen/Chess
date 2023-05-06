#pragma once
#include <iostream>
#include <cmath>
#include <string>

class FileVerifier{

public:
    int getVerificationKeyForFile(const std::string & fileContent);
    bool verifyFile(const std::string fileContent, const int verificationKey);

private:
    int getHash(const std::string& str);
    const int KEY = 1234;
};

