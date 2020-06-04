#include <iostream>

#include "app/ColorTriangle.h"
#include "app/HelloTriangle.h"
#include "app/TexturedQuad.h"
#include "app/TexturedTriangle.h"
//#include "app/ImguiDemo.h"
//#include "app/ModelLoad.h"

int guardedMain(int argc, char** argv)
{
    TexturedQuad app;
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