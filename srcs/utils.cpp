#include "utils.hpp"

void	trim(std::string &str, const std::string &delim)
{
	str.erase(str.find_last_not_of(delim) + 1);
	str.erase(0, str.find_first_not_of(delim));
}

std::string	readFile(const std::string &path)
{
	std::ifstream		fin(path.c_str());
	std::string			line;
	std::stringstream	ss;

	if (!fin.is_open())
		throw "Failed to open file!";
	while (std::getline(fin, line))
		ss << line << std::endl;
	return (ss.str());
}

std::vector<std::string>	split(std::string str, const std::string &delim)
{
	std::vector<std::string>	ret;
	trim(str, delim);
	while (str.size())
	{
		ret.push_back(str.substr(0, str.find_first_of(delim)));
		str.erase(0, str.find_first_of(delim));
		trim(str, delim);
	}
	return ret;
}
