
  #include <unistd.h>
  #include <fstream>
int main(int iiii, char **ahh, char **vhh)
{
    char buff[10]; 
    std::fstream fd("file_test_kakak", std::ios::out);
    read(0, buff, 9);
    write(1, buff, 10);
    fd << buff << std::endl;
}