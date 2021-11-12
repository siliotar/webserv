#include "Request.hpp"
#include "Color.hpp"
void Request::operationInit( void )
{
	_mapFoo["Accept-Encoding:"] = &Request::AcceptEncoding;
	_mapFoo["Accept:"] = &Request::accept;
	_mapFoo["Accept-Language:"] = &Request::AcceptLanguage;
	_mapFoo["Authorization:"] = &Request::Authorization;
	_mapFoo["Connection:"] = &Request::Conection;
	_mapFoo["Data:"] = &Request::Data;
	_mapFoo["From:"] = &Request::From;
	_mapFoo["Host:"] = &Request::Host;
	_mapFoo["If-Match:"] = &Request::IfMatch;
	_mapFoo["If-Modified-Since:"] = &Request::IfModifiedSince;
	_mapFoo["If-None-Match:"] = &Request::IfNoneMatch;
	_mapFoo["If-Range:"] = &Request::IfRange;
	_mapFoo["If-Unmodified-Since:"] = &Request::IfUnmodifiedSince;
	_mapFoo["Referer:"] = &Request::Referer;
	_mapFoo["UserAgent:"] = &Request::UserAgent;
}

void	Request::responseMethod( void )
{
	// _methods.push_back("GET");
	// _methods.push_back("POST");
	// _methods.push_back("DELETE");
	_methods.push_back("PUT");
	_methods.push_back("HEAD");
	_methods.push_back("CONNECT");
	_methods.push_back("HEAD");
	_methods.push_back("OPTIONS");
	_methods.push_back("PATCH");
	_methods.push_back("TRACE");
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
		
		std::map<std::string, void (Request::*)(const std::string &)>::iterator it;
		it = _mapFoo.find(key);
		if (it != _mapFoo.end())
			(this->*(it->second))(value);
	}
	if (_response == "POST")
		while (ss)	{
			std::getline (ss, str);
			if (str != "\n")
			{
				int k = str.find("=");
				_dataBaseMap[str.substr(0, k)] = str.substr(k + 1);
			}
	}
}

Request::Request(const std::string & content) : _errorFlag(200)
{
	responseMethod();
	std::string str;
	std::istringstream ss(content);
	operationInit();
	std::getline(ss, str);
	std::istringstream s(str);
	s >> _response >> _path >> _version;
	

	parsPath();
	try {
		if (_response == "GET" || _response == "POST" || _response == "DELETE")
			parsResponse(ss, str);
		else if (std::find(_methods.begin(), _methods.end(), _response) == _methods.end())
			throw "400";
		else
			throw "405";
	}
	catch (const char * error) {
		_errorFlag = atoi(error);
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
		exit (0); //kill user or serwer
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

Request::~Request() { }
