
  #include <unistd.h>
  #include <fstream>
  #include <iostream>
int main(int iiii, char **ahh, char **vhh)
{
    static char buff[10]; 
    read(0, buff, 9);
    buff[0] = '4';
    write(1, buff, 9);

}