#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <string>

#define VALID_VERSION "HTTP/1.1"

class Request {

    public:
        Request(const char *content)
        {
            std::string str;
            std::istringstream ss(content);
            std::getline(ss, str);
            std::istringstream s(str);
            s >> str >> _path >> _version;
            if (_version != VALID_VERSION)
                throw ("Invald version!");
            while (ss)
            {
                std::getline(ss, str);
                if (str != "")
                {
                    s.clear();
                    s.str(str);
                    std::string key;
                    s >> key;
                    std::string value;
                    std::getline(s, value);
                    _param.insert(make_pair(key, value));
                }
            }       
        }
    protected:
        std::string _path;
        
        std::string _version;
        std::map<std::string, std::string> _param;
        char *_reponse;
        int _reponse_size;
};