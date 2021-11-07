#pragma once

class ServerConfig;

#include <vector>
#include <set>
#include "ServerConfig.hpp"
#include "t_listen.hpp"

class Server
{
	private:
		ServerConfig		*_config;
		std::set<int>			_ports;

		Server();
		Server(const Server& copy);
		Server	&operator=(const Server& other);
	public:
		Server(ServerConfig &config);
		~Server();

		bool					isListen(unsigned int port) const;
		bool					containsName(const std::string &name);
		const std::set<int>		&getPorts() const;
		Location			*getLocation(const std::string &path);
};
