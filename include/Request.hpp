#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "Color.hpp"
#include <sstream>
#include <string>
#include <set>
#include "Server.hpp"
#include "../include/utils.hpp"
#define VALID_VERSION "HTTP/1.1"
#define A_Z "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define a_z "abcdefghijklmnopqrstuvwxyz"
#define Num "0123456789"
#define NOT_DISPLAYED "\0\1\2\3\4\5\6\7\10\12\13\14\16\17\20\21\22\23\24\25\26\27\30\31\32\33\34\35\36\37\127"




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
		std::vector<std::string> _cookieData;
		std::vector<std::string> _ifMatch;
		std::string _dataIfModifiedSince;
		std::vector<std::string> _ifNoneMatch;
		std::string _ifRange;
		std::string _ifUnmodifiedSince;
		std::string _referer;
		std::vector<std::pair<std::string, double> > _tE;
		std::string _UserAgent;


		std::vector<std::string>	_cgiArg;

		Location	*_locationConfig;
		std::string _bodyResponse;
		std::string _postContentType;
		std::string _postContentLength;
		std::string _response;
		std::string _path;
		std::string _location;
		std::string _version;
		std::map<std::string, std::string> _param;

		static std::vector<std::string> 	_methods;
		static std::map<std::string, void (Request::*)(const std::string &)> _mapFoo;

		int 				_errorFlag;
		Server				*_server;

		static std::vector<std::string> responseMethod( void );

		static std::map<std::string, void (Request::*)(const std::string &)> operationInit( void );

		void parsPath( void );
 
		void accept(const std::string & str);

		void parsResponse( std::istringstream & ss, std::string & str );

		void AcceptEncoding(const std::string & str);

		void AcceptLanguage(const std::string & str);

		void Authorization(const std::string & str);

		void CacheControl(const std::string & str);

		void Conection(const std::string & str);

		void Data(const std::string & str);

		void From(const std::string & str);

		void Host(const std::string & str);

		void IfMatch(const std::string & str);

		void IfModifiedSince(const std::string & str);

		void IfNoneMatch(const std::string & str);

		void IfRange(const std::string & str);

		void IfUnmodifiedSince(const std::string & str);

		void ProxyAuthorization(const std::string & str);

		void Range(const std::string & str);

		void Referer(const std::string & str);

		void TE(const std::string & str);

		void UserAgent(const std::string & str);
	
		void anyHeaders(const std::string & str);

		void ContentLength(const std::string & str);

		void SetCookie(const std::string & str);

		void ContentType(const std::string & str);

		Request();

		Request(const Request &);

		Request & operator=(const Request &);

	public:
		Request(const std::string & content, Server *);

		virtual ~Request();

};