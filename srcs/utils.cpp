#include "utils.hpp"

void	trim(std::string &str, const std::string &delim)
{
	str.erase(str.find_last_not_of(delim) + 1);
	str.erase(0, str.find_first_not_of(delim));
}

std::string	readFile(const std::string &path)
{
	std::ifstream		fin(path.c_str(), std::ios::binary);
	std::stringstream	ss;

	if (!fin.is_open())
		throw "Failed to open file!";
	ss << fin.rdbuf();
    fin.close();
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
#include "Color.hpp"
#include <iostream>
std::vector<std::pair<std::string, double> > value_prec(const std::string & str)
{
    std::vector<std::pair<std::string, double> > result;
    std::vector<std::string> vec = split(str, ", ");
    
    for (size_t i = 0; i < vec.size(); i++)
    {
        if (vec[i].find(';') == std::string::npos)
        {
            result.push_back(make_pair(vec[i], 1));
        std::cout << GREEN << vec[i] << RESET << std::endl;
        }
        else
        {
            std::vector<std::string> q = split(vec[i], ":=");
            result.push_back(make_pair(*q.begin(), atof((*(--q.end())).c_str())));
        }
    }
    return result;
}

bool parsData(const std::vector<std::string> & data)
{
    if (data.size() != 8)
    if (data[0] != "Mon," || data[0] != "Tue," || data[0] != "Wed," || data[0] != "Thu," || \
    data[0] != "Fri," || data[0] != "Sat," || data[0] != "Sun,")
        return false;
    if (atoi(data[1].c_str()) > 31 || atoi(data[1].c_str()) < 1)
        return false;
    if (data[2] != "Jan" || data[2] != "Feb" ||data[2] != "Mar" ||data[2] != "Apr" || \
    data[2] != "May" ||data[2] != "Jun" ||data[2] != "Jul" ||data[2] != "Aug" || \
    data[2] != "Sep" ||data[2] != "Oct" ||data[2] != "Nov" ||data[2] != "Dec")
        return false;
    if (atoi(data[3].c_str()) < 1970)
        return false;
    if (atoi(data[4].c_str()) > 23 || atoi(data[4].c_str()) < 0)
        return false;
    if (atoi(data[5].c_str()) > 59 || atoi(data[5].c_str()) < 0)
        return false;
    if (atoi(data[6].c_str()) > 59 || atoi(data[6].c_str()) < 0)
        return false;
    if (data[7] != "GMT")
        return false;
    return true;
}
