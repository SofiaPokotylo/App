#include <windows.h>
#include <iostream>
#include "search.h"

int main(int argc, char* argv[]){
    std::string name;
    int n = 8;
    std::cout<<"\nPlease, enter the name of the file\n";
    std::cin>>name;
    name.insert(0,"C:\\");
    name.append(".*");
    if(!seek(name.c_str(), FALSE)){
        if(!seek_thread(name.c_str(),n))
            std::cout<<"Such file doesn`t exist. Check the name of the file.";
    }
    return 0;
}