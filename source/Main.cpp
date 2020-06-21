#include <iostream>

#include "app/LookAroundCamera.h"

int guardedMain(int argc, char** argv)
{
    LookAroundCamera app;
    return app.run();
}

int main(int argc, char** argv)
{
    try
    {
        return guardedMain(argc, argv);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}