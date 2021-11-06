#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

void    					trim(std::string &str, const std::string &delim = " \t\n\r\f\v");
std::string					readFile(const std::string &path);
std::vector<std::string>	split(std::string str, const std::string &delim = " \t\n\r\f\v");
bool						parsData(const std::vector<std::string> &);
std::vector<std::pair<std::string, double> >	value_prec(const std::string &);
