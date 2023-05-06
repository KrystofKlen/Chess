#include "Application/Application.h"
#include "config/conf.cpp"

int main(){

    readFromConfigFileAndSetVariables();
    Application app;
    app.launch();
    return 0;
}