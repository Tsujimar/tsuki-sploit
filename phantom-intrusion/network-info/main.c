#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <Iphlpapi.h>
#include <winsock.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "wsock32.lib")

void getConnectedDevices()
{
    FILE *file = fopen("network_info.txt", "w");
    DWORD bufferSize = 0;
    DWORD retVal = GetIpNetTable(NULL, &bufferSize, FALSE);
    if (retVal == ERROR_INSUFFICIENT_BUFFER)
    {
        MIB_IPNETTABLE *table = (MIB_IPNETTABLE *)malloc(bufferSize);
        retVal = GetIpNetTable(table, &bufferSize, FALSE);
        if (retVal == NO_ERROR)
        {
            for (int i = 0; i < table->dwNumEntries; i++)
            {
                fprintf(file, "IP: %s\n", inet_ntoa(*(struct in_addr *)&table->table[i].dwAddr));
                fprintf(file, "MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
                        table->table[i].bPhysAddr[0],
                        table->table[i].bPhysAddr[1],
                        table->table[i].bPhysAddr[2],
                        table->table[i].bPhysAddr[3],
                        table->table[i].bPhysAddr[4],
                        table->table[i].bPhysAddr[5]);
            }
        }
        free(table);
    }
    fclose(file);
}

int main()
{
    getConnectedDevices();
    return 0;
}