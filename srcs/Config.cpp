#include "Config.hpp"

Config::Config(const char *path)
{
	std::ifstream	fin(path);
	std::string		line;
	std::stringstream	ss;

	if (!fin.is_open())
		throw "Failed to open config file!";
	while (std::getline(fin, line))
	{
		trim(line);
		if (line[0] != '#' && line.length() > 0)
			ss << line << std::endl;
	}
	std::string	config = ss.str();
	for (std::string tmp = getServer(config); tmp.length() > 0; tmp = getServer(config))
	{
		_servers.push_back(new ServerConfig(tmp));
		// std::cout << tmp << std::endl;
	}
}

std::string	Config::getServer(std::string &config)
{
	std::stringstream	server;
	std::string			line;
	int					opened = 1;
	int					closed = 0;
	size_t				pos = 0;
	const char			*skip = " \t\n\r\f\v{";

	trim(config);
	if (config.length() == 0)
		return "";
	if (config.compare(0, 6, "server") || config.find_first_of('{', 6) > config.find_first_not_of(skip, 6))
		throw "Wrong Config!";
	config.erase(0, config.find_first_not_of(skip, 6));
	while (opened != closed)
	{
		if (config.find_first_of('}', pos + 1) == std::string::npos)
			throw "Wrong Config!";
		if (config.find_first_of('{', pos + 1) < config.find_first_of('}', pos + 1))
		{
			pos = config.find_first_of('{', pos + 1);
			++opened;
		}
		else
		{
			pos = config.find_first_of('}', pos + 1);
			++closed;
		}
	}
	std::string	result(config.substr(0, pos));
	config.erase(0, pos + 1);
	return result;
}

Config::~Config()
{
	// for (size_t i = 0; i < _servers.size(); ++i)
	// {
	// 	delete _servers[i];
	// }
}

const std::vector<ServerConfig *>	Config::getServers() const
{
	return _servers;
}
