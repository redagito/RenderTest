#include <iostream>

#include "app/SimpleMoveCamera.h"

int guardedMain(int argc, char** argv)
{
    SimpleMoveCamera app;
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