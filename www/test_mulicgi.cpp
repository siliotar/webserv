#include <unistd.h>
#include <fstream>
#include <iostream>
int main(int iiii, char **argv, char **envp)
{
    static char buff[10]; 
    read(0, buff, 3);
    
    while (*envp)
    {

    }
}