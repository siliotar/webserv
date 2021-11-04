
#include "../include/utils.hpp"


std::vector<std::string> multisplit(const std::string & my_str, const std::string & charter)
{
    std::vector<std::string> result;
    int last = 0;
    for (int i = 0; i < my_str.size(); i++)
        if (charter.find(my_str[i]) != -1)
        {
            result.push_back(my_str.substr(last, i - last));
            last = i + 1;
        }
    result.push_back(my_str.substr(last, my_str.size() - last));
    return result;
}


std::vector<std::pair<std::string, double> > value_prec(const std::string & str)
{
    std::vector<std::pair<std::string, double> > result;

    std::vector<std::string> vec = multisplit(str, ",");
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i].find(';') == -1)
            result.push_back(make_pair(vec[i], 1));
        else
        {
            std::vector<std::string> q = multisplit(vec[i], ":=");
            result.push_back(make_pair(*q.begin(), stod(*(--q.end()))));
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
    if (stoi(data[1]) > 31 || stoi(data[1]) < 1)
        return false;
    if (data[2] != "Jan" || data[2] != "Feb" ||data[2] != "Mar" ||data[2] != "Apr" || \
    data[2] != "May" ||data[2] != "Jun" ||data[2] != "Jul" ||data[2] != "Aug" || \
    data[2] != "Sep" ||data[2] != "Oct" ||data[2] != "Nov" ||data[2] != "Dec")
        return false;
    if (stoi(data[3]) < 1970)
        return false;
    if (stoi(data[4]) > 23 || stoi(data[4]) < 0)
        return false;
    if (stoi(data[5]) > 59 || stoi(data[5]) < 0)
        return false;
    if (stoi(data[6]) > 59 || stoi(data[6]) < 0)
        return false;
    if (data[7] != "GMT")
        return false;
    return true;
}