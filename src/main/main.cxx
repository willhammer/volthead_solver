#include "volthead_main_config.h"
#include <iostream>  
#include <cstdlib>
#include <string>
#include <sstream>
#include <conio.h>
#include <Python.h>

namespace
{
    void print_version(int argc, char **argv)
    {
        if(argc < 1)
            return;

        printf("%s Version %d.%d\n", argv[0], volthead_main_VERSION_MAJOR, volthead_main_VERSION_MINOR);
        printf("Usage: %s number\n", argv[0]);
    }

    void print_cpp_standard(int argc, char **argv)
    {
        if(argc < 2)
            return;

        const double inputValue = std::stod(argv[1]);
    }

    void print_dirs()
    {
        printf("SOURCE DIR: %s\n", volthead_main_SOURCE_DIR);
        printf("BINARY DIR: %s\n", volthead_main_BIN_DIR);
    }

    int RunBasePy()
    {
        PyObject* pInt = nullptr;
        Py_Initialize();
        PyRun_SimpleString("print('Hello World from Embedded Python!!!')");
        Py_Finalize();
        printf("\nPress any key to exit...\n");
        int a;
        std::cin >> a;

        return 0;
    }
}

int main(int argc, char **argv)
{
    if(argc < 1)
        return 0;

    print_version(argc, argv);    
    print_dirs();

    RunBasePy();

    return 1;
}

  