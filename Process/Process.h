//
// Created by auax on 17/10/2022.
//

#ifndef PROCESS_INJECTOR_PROCESS_H
#define PROCESS_INJECTOR_PROCESS_H

#include <windows.h>

class Process {
public:
    static uint32_t getProcId(const char *process_name);

    static int injectDll(const char *dllName, DWORD pid);
};


#endif //PROCESS_INJECTOR_PROCESS_H
