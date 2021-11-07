#include "ServerConfig.hpp"

ServerConfig::ServerConfig(const std::string &config)
{
	std::stringstream			ss(config);
	std::string					line;
	std::vector<std::string>	splitedLine;

	while (std::getline(ss, line))
	{
		splitedLine = split(line);
		if (splitedLine[0] == "listen")
		{
			if (splitedLine.size() != 2)
				throw "Wrong config!";
			std::vector<std::string>	tmp = split(splitedLine[1], ":");
			if (tmp.size() != 2)
				throw "Wrong config!";
			std::vector<std::string>	host = split(tmp[0], ".");
			if (host.size() != 4)
				throw "Wrong config!";
			if (host[0].find_first_not_of("0123456789") != std::string::npos || \
				host[1].find_first_not_of("0123456789") != std::string::npos || \
				host[2].find_first_not_of("0123456789") != std::string::npos || \
				host[3].find_first_not_of("0123456789") != std::string::npos || \
				tmp[1].find_first_not_of("0123456789") != std::string::npos)
				throw "Wrong config!";
			unsigned int	inaddr = atoi(host[0].c_str()) << 24 | atoi(host[1].c_str()) << 16 | atoi(host[2].c_str()) << 8 | atoi(host[3].c_str());
			unsigned int	port = atoi(tmp[1].c_str());
			_listens.push_back(t_listen(inaddr, port));
			continue ;
		}
		if (splitedLine[0] == "server_name")
		{
			if (splitedLine.size() < 2)
				throw "Wrong config!";
			_names.insert(_names.end(), splitedLine.begin() + 1, splitedLine.end());
			continue ;
		}
		if (splitedLine[0] == "location")
		{
			if (splitedLine.size() != 3 || splitedLine[2] != "{")
				throw "Wrong config!";
			std::string	loc = splitedLine[1];
			_locations[loc] = new Location();
			_locations[loc]->setName(loc);
			while (std::getline(ss, line) && line != "}")
				_locations[loc]->parseLocation(split(line));
			continue ;
		}
		if (!parseLocation(splitedLine))
			throw "Wrong config!";
	}
	if (_root == "")
		_root = "/";
	std::map<std::string, Location *>::iterator		it = _locations.begin();
	for (; it != _locations.end(); ++it)
		if (it->second->getRoot() == "")
			it->second->setRoot(_root);
}

ServerConfig::~ServerConfig()
{
	std::map<std::string, Location *>::iterator	it = _locations.begin();

	for (; it != _locations.end(); ++it)
	{
		delete (*it).second;
	}
}

const std::vector<t_listen>				&ServerConfig::getListens() const
{
	return _listens;
}

const std::vector<std::string>			&ServerConfig::getNames() const
{
	return _names;
}

const std::map<std::string, Location *>	&ServerConfig::getLocations() const
{
	return _locations;
}
