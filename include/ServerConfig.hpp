#pragma once

#include <vector>
#include <string>
#include <sstream>
#include "Location.hpp"

typedef struct s_listen
{
	unsigned int	inaddr;
	unsigned int	port;
	s_listen(unsigned int addr, unsigned int port)
	: inaddr(addr), port(port)
	{}
}t_listen;

class ServerConfig : public Location
{
	private:
		std::vector<t_listen>				_listens;
		std::vector<std::string>			_names;
		std::map<std::string, Location *>	_locations;

		ServerConfig();
		ServerConfig(const ServerConfig& copy);
		ServerConfig	&operator=(const ServerConfig& other);
	public:
		ServerConfig(const std::string &config);
		virtual ~ServerConfig();
};
