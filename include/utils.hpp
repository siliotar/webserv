#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>

std::vector<std::string> multisplit(const std::string &, const std::string & );

std::vector<std::pair<std::string, double> > value_prec(const std::string &);

bool parsData(const std::vector<std::string> &);