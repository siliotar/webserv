#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <unistd.h>

void    					trim(std::string &str, const std::string &delim = " \t\n\r\f\v");
std::string					readFile(const std::string &path);
std::vector<std::string>	split(std::string str, const std::string &delim = " \t\n\r\f\v");
bool						parsData(const std::vector<std::string> &);
std::vector<std::pair<std::string, double> >	value_prec(const std::string &);

//                          c_function.cpp
int			                c_get_next_line(int fd, char **line);
int		                    ft_strlen(const char *str);
char	                    *find_new_line(char *buff);
char	                    *ft_strjoin(const char *str1, const char *str2);
char	                    *ft_strdup(const char *str);
