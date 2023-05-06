#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winreg.h>

char *printRegGetValue(HKEY hKey, const char *subKey, const char *valueName)
{
    HKEY hSubKey;
    if (RegOpenKeyExA(hKey, subKey, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS)
    {
        DWORD dataSize;
        if (RegQueryValueExA(hSubKey, valueName, NULL, NULL, NULL, &dataSize) == ERROR_SUCCESS)
        {
            char *data = (char *)malloc(dataSize);
            if (RegQueryValueExA(hSubKey, valueName, NULL, NULL, (LPBYTE)data, &dataSize) == ERROR_SUCCESS)
            {
                RegCloseKey(hSubKey);
                return data;
            }
            free(data);
        }
        RegCloseKey(hSubKey);
    }
    return NULL;
}

void collectDeviceInfo()
{
    FILE *file = fopen("user_harvest.txt", "w");
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD computerNameSize = sizeof(computerName);
    if (GetComputerNameA(computerName, &computerNameSize))
    {
        fprintf(file, "Computer Name: %s\n", computerName);
    }

    char username[MAX_PATH];
    DWORD usernameSize = sizeof(username);
    if (GetUserNameA(username, &usernameSize))
    {
        fprintf(file, "Username: %s\n", username);
    }

    OSVERSIONINFOA osVersion;
    osVersion.dwOSVersionInfoSize = sizeof(osVersion);
    if (GetVersionExA((OSVERSIONINFOA *)&osVersion))
    {
        fprintf(file, "OS Version: %d.%d\n", osVersion.dwMajorVersion, osVersion.dwMinorVersion);
    }

    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    fprintf(file, "Processor Architecture: %d-bit\n", systemInfo.wProcessorArchitecture * 8);

    char *baseBoardManufacturer = printRegGetValue(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardManufacturer");
    char *baseBoardProduct = printRegGetValue(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardProduct");
    fprintf(file, "BaseBoardManufacturer: %s\n", baseBoardManufacturer);
    fprintf(file, "BaseBoardProduct: %s\n", baseBoardProduct);
    free(baseBoardManufacturer);
    free(baseBoardProduct);

    fclose(file);
}

int main()
{
    collectDeviceInfo();
    return 0;
}