#pragma once

#include <map>
#include <string>

class MIME
{
	private:
		MIME();
		MIME(const MIME& copy);
		MIME	&operator=(const MIME& other);
		virtual ~MIME();
	public:
		static const std::map<std::string, std::string>	_types;
		static const std::map<std::string, std::string>	createMap();

		static const std::string	&getType(const std::string &extension);
};
