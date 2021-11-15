#include "Request.hpp"
#include "Color.hpp"

std::map<std::string, void (Request::*)(const std::string &)> Request::_mapFoo = Request::operationInit();

std::vector<std::string> 	Request::_methods = Request::responseMethod();
std::map<std::string, void (Request::*)(const std::string &)> Request::operationInit( void )
{
	std::map<std::string, void (Request::*)(const std::string &)> m;
	m["Accept-Encoding:"] = &Request::AcceptEncoding;
	m["Accept:"] = &Request::accept;
	m["Accept-Language:"] = &Request::AcceptLanguage;
	m["Authorization:"] = &Request::Authorization;
	m["Connection:"] = &Request::Conection;
	m["Data:"] = &Request::Data;
	m["From:"] = &Request::From;
	m["Host:"] = &Request::Host;
	m["If-Match:"] = &Request::IfMatch;
	m["If-Modified-Since:"] = &Request::IfModifiedSince;
	m["If-None-Match:"] = &Request::IfNoneMatch;
	m["If-Range:"] = &Request::IfRange;
	m["If-Unmodified-Since:"] = &Request::IfUnmodifiedSince;
	m["Referer:"] = &Request::Referer;
	m["UserAgent:"] = &Request::UserAgent;
	m["Pragma:"] = &Request::anyHeaders;
	m["Sec-Fetch-Site:"] = &Request::anyHeaders;
	m["Sec-Fetch-Mode:"] = &Request::anyHeaders;
	m["Sec-Fetch-Dest:"] = &Request::anyHeaders;
	m["Cache-Control:"] = &Request::anyHeaders;
	m["sec-ch-ua:"] = &Request::anyHeaders;
	m["sec-ch-ua-mobile:"] = &Request::anyHeaders;
	m["User-Agent:"] = &Request::anyHeaders;
	m["sec-ch-ua-platform:"] = &Request::anyHeaders;
	m["Upgrade-Insecure-Requests:"] = &Request::anyHeaders;
	m["Sec-Fetch-User:"] = &Request::anyHeaders;
	m["Purpose:"] = &Request::anyHeaders;

	return m;
}

std::vector<std::string>	Request::responseMethod( void )
{
	std::vector<std::string> a;
	a.push_back("PUT");
	a.push_back("HEAD");
	a.push_back("CONNECT");
	a.push_back("HEAD");
	a.push_back("OPTIONS");
	a.push_back("PATCH");
	a.push_back("TRACE");
	return a;
}

Request::Request(const std::string & content) : _errorFlag(200)
{
	std::string str;
	std::istringstream ss(content);
	std::getline(ss, str);
	std::istringstream s(str);
	s >> _response >> _path >> _version;
	parsPath();
	try {
		if (_response == "GET" || _response == "POST" || _response == "DELETE")
			parsResponse(ss, str);
		else if (std::find(_methods.begin(), _methods.end(), _response) == _methods.end())
			throw "400::findmethod";
		else
			throw "405::findmethod";
	}
	catch (const char * error) {
		std::cout << RED << error << RESET << std::endl;
		_errorFlag = atoi(error);
	}
}

void Request::parsResponse(std::istringstream & ss, std::string & str)
{

	
	std::stringstream s;
	_location = _path;
	if (_version != VALID_VERSION)
		throw ("505:version");
	while (ss) {
		std::getline(ss, str);
		if (str == "\r\n" || str == "\n" || str == "\r")
			break;
		s.clear();
		if (str[str.size() - 1] == '\r')
			str = str.substr(0, str.size() - 1);
		s.str(str);
		std::string key;
		s >> key;
		std::string value;
		std::getline(s, value);
		if (key == "")
			continue;
		std::map<std::string, void (Request::*)(const std::string &)>::iterator it;
		it = _mapFoo.find(key);
		if (it != _mapFoo.end())
			(this->*(it->second))(value);
		else
		{
			if (key.size() >= 2 && key[key.size() - 1] == ':')
			{
				std::string tmp = A_Z; 
				tmp += a_z  + std::string(":-") + Num;
				int w = key.find_first_not_of(tmp);
				if (w != -1)
				{
					std::cout << w << " " << key << std::endl;
					throw ("400::method1");
				}
			}
			else
				throw ("400::method");
		}
	}
	if (_response == "POST")
		while (ss)	{
			std::getline (ss, str);
			if (str != "\n")
				_postResponse += str;
	}
}


void Request::parsPath() {
	size_t a;
	while ((a = _path.find("%20")) != std::string::npos)
		_path.replace(a, 3, " ");	
}
// what do this information??
void Request::accept(const std::string & str) {

	std::string tmp; 
	tmp += std::string(NOT_DISPLAYED) + "():<>?@[\\]{}";
	if (str.find_first_of(tmp) != std::string::npos)
		throw("406:AcceptEncoding");
	_accept = value_prec(str);
}

void Request::AcceptEncoding(const std::string & str) {
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

	for (size_t i = 0; i < _acceptEncoding.size(); i++)
	{
		std::set<std::string>::iterator it = correct_str.find(_acceptEncoding[i].first);
		if (it == correct_str.end())
			throw("406:AcceptEncoding");
	}
}

void Request::AcceptLanguage(const std::string & str) {
	std::string tmp; 
	tmp += std::string(A_Z) + std::string(a_z) + std::string(Num) + "*,-.;= \15";
	if (str.find_first_not_of(tmp) != std::string::npos)
		throw("406:AcceptLanguage");
	_acceptLanguage = value_prec(str); 
}

void Request::Authorization(const std::string & str) {
	std::vector<std::string> vec = split(str, " ,");
	if (vec[0] == "Basic") {
		
	}
	else if (vec[0] == "Digest") {
		
	}
	else
		throw ("400:Authorization");
}

void Request::CacheControl(const std::string & str)
{
	std::vector<std::string> tmp;
	_cacheControl.push_back(str);
}

void Request::Conection(const std::string & str)
{
	if (str == " close") {
		throw("400:Conection");
	}
	else if (str != " keep-alive")
		throw("400:Conection");
}

void Request::Data(const std::string & str)
{
		std::vector<std::string> data = split(str, " :");
	if (!parsData(data))
		throw ("400:Data");
	_dataMassage = str;
}

void Request::From(const std::string & str) {
	std::istringstream ss(str);
	std::string tmp;
	ss >> tmp;
	if (ss) {
		throw ("400:From");
	}
	_mail = tmp;
}

void Request::Host(const std::string & str) {
	std::vector<std::string> tmp = split(str, ":");
	if (tmp.size() != 2)
		throw ("400:Host");
	_host = tmp[0];
	_port = tmp[1];
}

void Request::IfMatch(const std::string & str) {
	_ifMatch = split(str, " ");
	if (_ifMatch.size() < 1)
		throw ("400:IfMatch");
}

void Request::IfModifiedSince(const std::string & str) {
		std::vector<std::string> data = split(str, " :");
		if (!parsData(data))
		throw ("400:IfModifiedSince");
	_dataIfModifiedSince = str;
}

void Request::IfNoneMatch(const std::string & str) {
	_ifNoneMatch = split(str, " ");
	if (_ifNoneMatch.size() < 1)
		throw ("400:IfNoneMatch");
}

void Request::IfRange(const std::string & str) {
	std::vector<std::string> data = split(str, " :");
	if (data.size() == 1)
	{
		_ifRange = str;
		return ;
	}
	if (!parsData(data))
		throw ("400:IfRange");
	_ifRange = str;
}

void Request::IfUnmodifiedSince(const std::string & str) {
		std::vector<std::string> data = split(str, " :");
		if (!parsData(data))
		throw ("400:IfUnmodifiedSince"); 
	_ifUnmodifiedSince = str;
}
void ProxyAuthorization(const std::string & str){
	(void)str;
}
void Request::Range(const std::string & str) {
	(void)str;
}

void Request::Referer(const std::string & str) {
	_referer = str;
}

void Request::TE(const std::string & str) {
	std::vector<std::pair<std::string, double> > tmp;
	tmp = value_prec(str);
	_tE.insert(_tE.end(), tmp.begin(), tmp.end());
	std::set<std::string> correct_str;
	correct_str.insert("gzip");
	correct_str.insert("compress");
	correct_str.insert("deflate");
	correct_str.insert("trailers");
	for (size_t i = 0; i < _tE.size(); i++)
	{
		std::set<std::string>::iterator it = correct_str.find(_tE[i].first);
		if (it == correct_str.end())
			throw("400:TE");
	}
}

void Request::UserAgent(const std::string & str){
	_UserAgent = str;
}

void Request::anyHeaders(const std::string & str) {
	std::string s = str;
}
Request::~Request() { }

