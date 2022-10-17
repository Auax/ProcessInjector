//
// Created by auax on 17/10/2022.
//

#include <cstdio>
#include <cstring>
#include <Windows.h> // Always include windows before Win32 headers
#include <Tlhelp32.h>
#include <cstdint>

#include "Process.h"

uint32_t Process::getProcId(const char *process_name) {
    DWORD pid = 0;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(entry);
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    do {
        if (!strcmp(entry.szExeFile, process_name))
            pid = entry.th32ProcessID;
    } while (Process32Next(hSnapshot, &entry));
    CloseHandle(hSnapshot);
    return pid;
}

int Process::injectDll(const char dllName[], DWORD pid) {
    HANDLE hProcess; // process handle
    HANDLE hThread; // remote thread
    LPVOID lpBaseAddress; // remote buffer
    size_t sz = strlen(dllName);

    // handle to kernel32
    // kernel32.dllName file handles the memory usage in windows
    HMODULE hModule = GetModuleHandle("kernel32.dll");
    // GetProcAddress takes the DLL module handle and the name of the function you want to call.
    // LoadLibraryA is used to load a specified module into the address space of the calling process
    FARPROC lpStartAddress = GetProcAddress(hModule, "LoadLibraryA");

    if (pid == 0) {
        printf("Invalid PID. Exiting...\n");
        return -1;
    }

    // assign process handle
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, DWORD(pid));

    // allocate memory buffer for remote process
    // VirtualAllocEx allows to allocate memory for a given process, unlike VirtualAlloc, that only works for the calling process
    lpBaseAddress = VirtualAllocEx(hProcess, nullptr, sz, (MEM_RESERVE | MEM_COMMIT), PAGE_EXECUTE_READWRITE);

    // write dllName to process (inject)
    WriteProcessMemory(hProcess, lpBaseAddress, dllName, sz, nullptr);

    // create a new thread
    hThread = CreateRemoteThread(hProcess, nullptr, 0, (LPTHREAD_START_ROUTINE) lpStartAddress, lpBaseAddress, 0,
                                 nullptr);
    CloseHandle(hProcess);

    if (hThread) printf("Injection successful!\n");
    else printf("Injection unsuccessful!\n");

    return 0;
}

