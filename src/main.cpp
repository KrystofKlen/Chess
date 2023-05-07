#include "Application/Application.h"
#include "config/conf.cpp"

int main(){

    if(! readFromConfigFileAndSetVariables()){
        std::cout << "Couldn't read file.conf. Plase check that format of file.config is correct. Check README.md for more.\n";
        return 0;
    }

    Application app;
    app.launch();
    return 0;
}