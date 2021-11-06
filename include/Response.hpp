#pragma once
#include <iostream>
#include "Request.hpp"
#include <dirent.h>
#include <string.h>
#include <fstream>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <iomanip>
#include "Server.hpp"

class Response : public Request {

	private:
		const std::string 	_directoryListingDefult;
		std::string			_response;		
	public:
		Response(const std::string & request,const Server & _servers);
		// If autoindex on, open directory in html 
		std::string autoIndexOn( void );

		std::string autoIndexOff( void );
		
		void acceptRanges(const std::string & str);

		void age(const std::string & str);

		void alternates(const std::string & str);

		void contentDisposition ();

		void eTag();

		void location();

		void publicR( void );

		void retryAfter( void );

		void server( void );

		void vary();

		std::string getResponse( void );
};