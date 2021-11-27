#include <unistd.h>
#include <fstream>
#include <iostream>
int main(int iiii, char **argv, char **envp)
{
    static char buff[10]; 
    read(0, buff, 9);
    for (size_t i = 0; i < 9; ++i)
        buff[i] += buff[i] >= 'a' && buff[i] < 'z' ? 'A' - 'a' : 0;
    write(1, buff, 9);
}