#include "python_loader.hxx"
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <Python.h>

namespace Volthead
{
    namespace Python
    {
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
}