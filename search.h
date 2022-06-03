//
// Created by Asus on 03.06.2022.
//

#ifndef APP_SEARCH_H
#define APP_SEARCH_H
#include <windows.h>
#include <iostream>
#include <thread>

BOOL seek(LPCTSTR lpszFileName, BOOL bInnerFolders);
BOOL seek_thread(LPCTSTR lpszFileName, int n);
#endif //APP_SEARCH_H
