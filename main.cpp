#include <iostream>
#include "Process/Process.h"

int main(int argc, char **argv) {
#ifdef _WIN32 //|| _WIN64
    // Path to compiled dll (source=dll_inject.cpp)
    char dll[] = R"(C:\Users\ryux1\Desktop\Coding\C++\Projects\ProcessInjector\dll\dll-inject.dll)";
    // Get process id from process name
    DWORD pid = Process::getProcId(argv[1]);

    printf("PID: %i\n", pid);

    Process::injectDll(dll, pid);

#else
    // Avoid wine execution
    printf("Only Windows supported!");
#endif
    return 0;
}
