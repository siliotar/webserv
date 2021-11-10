#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <set>
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
		std::vector<std::string> _ifMatch;
		std::string _dataIfModifiedSince;
		std::vector<std::string> _ifNoneMatch;
		std::string _ifRange;
		std::string _ifUnmodifiedSince;
		std::string _referer;
		std::vector<std::pair<std::string, double> > _tE;
		std::string _UserAgent;

		std::map<std::string, std::string> _dataBaseMap;

		std::string _response;
		std::string _path;
		std::string _location;
		std::map<std::string, void (Request::*)(const std::string &)> _mapFoo;
		std::string _version;
		std::map<std::string, std::string> _param;

		void operationInit( void );

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

	public:
		Request(const std::string & content);
		virtual ~Request();

};