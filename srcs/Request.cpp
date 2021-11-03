// #pragma once
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include "../include/utils.hpp"
#define VALID_VERSION "HTTP/1.1"
#define A_Z "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define a_z "abcdefghijklmnopqrstuvwxyz"
#define NOT_DISPLAYED "\0\1\2\3\4\5\6\7\10\12\13\14\15\16\17\20\21\22\23\24\25\26\27\30\31\32\33\34\35\36\37\127"

class Request {


    protected:
        
        std::vector<std::pair<std::string, double> > _accept;
        std::vector<std::pair<std::string, double> > _acceptEncoding;
        std::vector<std::pair<std::string, double> > _acceptLanguage;
        std::vector<std::string> _authorization;
        std::vector<std::string> _cacheControl;
        std::string _dataMassage;
        std::string _mail;
        std::string _host;
        std::string _port;
        std::vector<std::string> _ifMatch;
        std::string _dataIfModifiedSince;
        std::vector<std::string> _ifNoneMatch;
        std::string _ifRange;
        std::string _ifUnmodifiedSince;
        std::string _referer;
        std::vector<std::pair<std::string, double> > _tE;
        std::string _UserAgent;




        std::string _path;
        std::unordered_map<std::string, void (Request::*)(const std::string &)> mapFoo;
        std::string _version;
        std::map<std::string, std::string> _param;
        char *_reponse;
        int _reponse_size;
        void operationInit( void )
        {
            mapFoo.insert(make_pair("Accept:", &Request::Accept));
            mapFoo.insert(make_pair("Accept-Encoding:", &Request::AcceptEncoding));
            mapFoo.insert(make_pair("Accept-Language:", &Request::AcceptLanguage));
            mapFoo.insert(make_pair("Authorization:", &Request::Authorization));
            mapFoo.insert(make_pair("Cache-Control:", &Request::Conection));
            mapFoo.insert(make_pair("Data:", &Request::Data));
            mapFoo.insert(make_pair("From:", &Request::From));
            mapFoo.insert(make_pair("Host:", &Request::Host));
            mapFoo.insert(make_pair("If-Match:", &Request::IfMatch));
            mapFoo.insert(make_pair("If-Modified-Since:", &Request::IfModifiedSince));
            mapFoo.insert(make_pair("If-None-Match:", &Request::IfNoneMatch));
            mapFoo.insert(make_pair("If-Range:", &Request::IfRange));

            mapFoo.insert(make_pair("If-Unmodified-Since:", &Request::IfUnmodifiedSince));
            mapFoo.insert(make_pair("Referer:", &Request::Referer));
            mapFoo.insert(make_pair("UserAgent:", &Request::UserAgent));




        }

    public:
        Request(const char *content)
        {
            std::string str;
            std::istringstream ss(content);
            std::istringstream s(str);
            
            operationInit();
            std::getline(ss, str);
            s >> str >> _path >> _version;
            if (_version != VALID_VERSION)
                throw ("Invald version!"); // ???????????????????
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
   
        // what do this information??
        void Accept(const std::string & str) {

            std::string tmp; 
            tmp += std::string(NOT_DISPLAYED) + "():<>?@[\\]{}";
            if (str.find_first_of(tmp) != std::string::npos)
                throw("406"); // ???????????????????
            //Use MIME pars not valid parametr
            //Use MIME
            //Use MIME
            //Use MIME
            //Use MIME
            //Use MIME
            //Use MIME
            //Use MIME
            _accept = value_prec(str);
        }

        void AcceptEncoding(const std::string & str) {
            std::vector<std::pair<std::string, double> > tmp;
            tmp = value_prec(str);
            _acceptEncoding.insert(_acceptEncoding.end(), tmp.begin(), tmp.end());
            std::set<std::string> correct_str;
            correct_str.insert("gzip");
            correct_str.insert("compress");
            correct_str.insert("deflate");
            correct_str.insert("br");
            correct_str.insert("identity");
            correct_str.insert("*");
            for (int i = 0; i < _acceptEncoding.size(); i++)
            {
                std::set<std::string>::iterator it = correct_str.find(_acceptEncoding[i].first);
                if (it == correct_str.end())
                    throw("406"); // ???????????????????
            }
        }

        void AcceptLanguage(const std::string & str) {
            std::string tmp; 
            tmp += std::string(A_Z) + std::string(a_z) + "*,-.;=";
            if (str.find_first_not_of(tmp) != std::string::npos)
                throw("406"); // ???????????????????
             _acceptLanguage = value_prec(str); 
        }

        void Authorization(const std::string & str) {
            std::vector<std::string> vec = multisplit(str, " ,");
            if (vec[0] == "Basic") {
                
            }
            else if (vec[0] == "Digest") {
                
            }
            else {
                throw ("406");  // ???????????????????
            }
            // ?
            // ?
            // ?
            // ?
        }

        void CacheControl(const std::string & str)
        {
            std::vector<std::string> tmp;
            _cacheControl.push_back(str);
        }

        void Conection(const std::string & str)
        {
            if (str == "close") {
                throw ("vam_ban"); // ???????????????????/
            }
            else if (str != "keep-alive") {
                throw("406"); // ?????????????????????/
            }
        }

        void Data(const std::string & str)
        {
             std::vector<std::string> data = multisplit(str, " :");
            if (!parsData(data))
                throw ("406::Data"); // ???????????? 
            _dataMassage = str;
        }

        void From(const std::string & str) {
            std::istringstream ss(str);
            std::string tmp;
            ss >> tmp;
            if (ss) {
                throw ("406"); // ??????????????
            }
            _mail = tmp;
        }

        void Host(const std::string & str) {
            std::vector<std::string> tmp = multisplit(str, ":");
            if (tmp.size() != 2)
                throw ("406::host"); //??????????????
            _host = tmp[0];
            _port = tmp[1];
        }

        void IfMatch(const std::string & str) {
            _ifMatch = multisplit(str, " ");
            if (_ifMatch.size() < 1)
                throw ("406::ifMatch"); // ???????????????
        }

        void IfModifiedSince(const std::string & str) {
             std::vector<std::string> data = multisplit(str, " :");
             if (!parsData(data))
                throw ("406::IfModifiedSince"); // ???????????? 
            _dataIfModifiedSince = str;
        }

        void IfNoneMatch(const std::string & str) {
            _ifNoneMatch = multisplit(str, " ");
            if (_ifNoneMatch.size() < 1)
                throw ("406::IfNoneMatch"); // ???????????????
        }

        void IfRange(const std::string & str) {
            std::vector<std::string> data = multisplit(str, " :");
            if (data.size() == 1)
            {
                _ifRange = str;
                return ;
            }
            if (!parsData(data))
                throw ("206::IfRange"); // ???????????? 
            _ifRange = str;
        }

        void IfUnmodifiedSince(const std::string & str) {
             std::vector<std::string> data = multisplit(str, " :");
             if (!parsData(data))
                throw ("406::IfModifiedSince"); // ???????????? 
            _ifUnmodifiedSince = str;
        }
        void ProxyAuthorization(const std::string & str){
            //????????????????????????????
            //????????????????????????????
            //????????????????????????????
            //????????????????????????????
            //????????????????????????????
            //????????????????????????????
        }
        void Range(const std::string & str) {

            //????????????????????????????
            //????????????????????????????
            //????????????????????????????
            //????????????????????????????
            //????????????????????????????
            //????????????????????????????
            //The server can also ignore the Range header and return the whole document with a 200 status code. OK))))
        }

        void Referer(const std::string & str) {
            _referer = str;
        }

        void TE(const std::string & str) {
            std::vector<std::pair<std::string, double> > tmp;
            tmp = value_prec(str);
            _tE.insert(_tE.end(), tmp.begin(), tmp.end());
            std::set<std::string> correct_str;
            correct_str.insert("gzip");
            correct_str.insert("compress");
            correct_str.insert("deflate");
            correct_str.insert("trailers");
            for (int i = 0; i < _tE.size(); i++)
            {
                std::set<std::string>::iterator it = correct_str.find(_tE[i].first);
                if (it == correct_str.end())
                    throw("406"); // ???????????????????
            }
        }

        void UserAgent(const std::string & str){
            _UserAgent = str;
            // kak zdes kakati
        }

};

int main()
{
    std::string str = "image/avif,image/webp,image/apng,image/svg+xml,image/*,*/*;q=0.8";
    std::string tmp; 
    tmp += std::string(NOT_DISPLAYED) + "():<>?@[\\]{}";
    std::vector<std::pair<std::string, double> > _accept;
    int a = stoi(std::string("124"));
    std::cout << a << std::endl;
    // if (str.find_first_of(tmp) != std::string::npos)
    // {
    //     std::cout << "BAN" << std::endl;
    // }
    // else
    // {
    //     _accept = value_prec(str);
    //     for (int i = 0; i < _accept.size(); i++)
    //         std::cout << _accept[i].first << " " << _accept[i].second << std::endl;
    // }
}