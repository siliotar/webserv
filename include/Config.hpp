#pragma once

class ServerConfig;

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "utils.hpp"
#include "ServerConfig.hpp"

class Config
{
	private:
		std::vector<ServerConfig *>	_servers;

		std::string	getServer(std::string &config);

		Config();
		Config(const Config& copy);
		Config	&operator=(const Config& other);
	public:
		Config(const char *path);
		virtual ~Config();
};
