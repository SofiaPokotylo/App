//
// Created by Asus on 03.06.2022.
//
#include "search.h"


static bool  k = false;
BOOL seek(LPCTSTR lpszFileName, BOOL bInnerFolders)
{
    LPTSTR part;
    char tmp[MAX_PATH];
    char name[MAX_PATH];

    if(k)
        return TRUE;

    HANDLE hSearch;
    WIN32_FIND_DATA wfd;
    memset(&wfd, 0, sizeof(WIN32_FIND_DATA));

    if(bInnerFolders)
    {
        if(GetFullPathName(lpszFileName, MAX_PATH, tmp, &part) == 0)
            return FALSE;
        lstrcpy(name, part);
        lstrcpy(part, "*.*");

        //if folder exists, down to it
        wfd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
        hSearch = FindFirstFile(tmp, &wfd);
        if (hSearch != INVALID_HANDLE_VALUE)
            do
            {
                //check if current folder is a service folder which no need to check
                if (!strncmp(wfd.cFileName, ".", 1) || !strncmp(wfd.cFileName, "..", 2))
                    continue;
                if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) //if it's a folder
                {
                    // making a new path
                    char next[MAX_PATH];
                    if(GetFullPathName(lpszFileName, MAX_PATH, next, &part) == 0) return FALSE;
                    lstrcpy(part, wfd.cFileName);
                    lstrcat(next, "\\");
                    lstrcat(next, name);

                    //recursive down
                    if(!seek(next, FALSE)) {
                        if (seek(next, TRUE)) {
                            return TRUE;
                        }
                    }
                    else
                        return TRUE;
                }
            }
            while (FindNextFile(hSearch, &wfd)); //finding next file in folder
        FindClose (hSearch); // closing a search descriptor
    }

    if ((hSearch = FindFirstFile(lpszFileName, &wfd)) == INVALID_HANDLE_VALUE)
        return FALSE;
    do
        if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) // is it's a file
        {
            char file[MAX_PATH];
            if(GetFullPathName(lpszFileName, MAX_PATH, file, &part) == 0) return FALSE;
            lstrcpy(part, wfd.cFileName);
            std::cout << file<< std::endl <<wfd.cFileName<< std::endl;
            k = true;
            return TRUE;
        }
    while (FindNextFile(hSearch, &wfd));	// next file in folder
    FindClose (hSearch);					// close search descriptor
    return FALSE;
}

BOOL seek_thread(LPCTSTR lpszFileName, int n){
    LPTSTR part;
    char tmp[MAX_PATH];
    char name[MAX_PATH];
    std::thread *thr = new std::thread[n];
    int i = 0;

    HANDLE hSearch;
    WIN32_FIND_DATA wfd;
    memset(&wfd, 0, sizeof(WIN32_FIND_DATA));

    if(GetFullPathName(lpszFileName, MAX_PATH, tmp, &part) == 0)
        return FALSE;
    lstrcpy(name, part);
    lstrcpy(part, "*.*");

    wfd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
    hSearch = FindFirstFile(tmp, &wfd);
    if (hSearch != INVALID_HANDLE_VALUE)
        do
        {
            if (!strncmp(wfd.cFileName, ".", 1) || !strncmp(wfd.cFileName, "..", 2))
                continue;
            if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                char next[MAX_PATH];
                if(GetFullPathName(lpszFileName, MAX_PATH, next, &part) == 0) return FALSE;
                lstrcpy(part, wfd.cFileName);
                lstrcat(next, "\\");
                lstrcat(next, name);

                if (!seek(next, FALSE)) {
                    if (i < n) {
                        thr[i] = std::thread(seek, next, TRUE);
                        ++i;
                    } else {
                        for (int j = 0; j < n; ++j) {
                            thr[j].join();
                        }
                        if (k) {
                            delete[] thr;
                            return TRUE;
                        } else {
                            i = 0;
                        }
                    }
                } else
                    return TRUE;
            }
        }
        while (FindNextFile(hSearch, &wfd));
    FindClose (hSearch);
    return FALSE;
}