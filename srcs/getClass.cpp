#include "getClass.hpp"


class getClass : Request {

    private:
        
    public:
        getClass(const char *content) : Request(content)
        {
            // std::cout << _path << " " << _version << std::endl;
            // for (std::map<std::string, std::string>::iterator it = _param.begin(); it != _param.end(); it++)
            // {
            //     std::cout << it->first << " " << it->second;
            //     std::cout << std::endl;
            // }
        }
        int getReponseSize() const {return _reponse_size; }
        char *getReponse() const { return _reponse; }
        

};

int main()
{
    char str[1000] = "GET / HTTP/1.1\nHost: localhost:8000\nConnection: keep-alive\nsec-ch-ua: \"Chromium\";v=\"94\", \"Google Chrome\";v=\"94\", \";Not A Brand\";v=\"99\"\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/94.0.4606.81 Safari/537.36";
    getClass a(str);

}