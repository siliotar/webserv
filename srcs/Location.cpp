#include "Location.hpp"

Location::Location() :
_autoindex(0), _name("/"), _root("/"), _errorPages(), _bodySize(1024 * 1024), _index("index.html")
{}

Location::~Location()
{}

bool							Location::isAutoindex() const
{
	return _autoindex;
}

size_t							Location::getBodySize() const
{
	return _bodySize;
}

const std::string				&Location::getName() const
{
	return _name;
}

const std::string				&Location::getRoot() const
{
	return _root;
}

const ReplyPages				&Location::getErrorPages() const
{
	return _errorPages;
}

const std::vector<std::string>	&Location::getAllowMethods() const
{
	return _allowMethods;
}

const std::string				&Location::getIndex() const
{
	return _index;
}

std::string						Location::getPath(const std::string &path) const
{
	size_t	pos;
	if ((pos = path.find(_name)) == std::string::npos)
		return path;
	std::string	res = path;
	return res.replace(pos, _name.size(), _root);
}

void							Location::setName(const std::string &name)
{
	_name = name;
}

bool	Location::parseLocation(const std::vector<std::string> &splitedLine)
{
	if (splitedLine[0] == "error_page")
	{
		if (splitedLine.size() < 3)
			throw "Wrong config!";
		for (size_t i = 1; i < splitedLine.size() - 1; ++i)
		{
			unsigned int	code = atoi(splitedLine[i].c_str());
			if (code < 400)
				throw "Wrong config!";
			_errorPages.setReplyBodyFromFile(code, splitedLine[splitedLine.size() - 1]);
		}
		return true;
	}
	if (splitedLine[0] == "client_max_body_size")
	{
		if (splitedLine.size() != 2)
			throw "Wrong config!";
		if (splitedLine[1].find_first_not_of("0123456789") != splitedLine[1].size() - 1)
			throw "Wrong config!";
		if (splitedLine[1].find_first_not_of("0123456789KM") != std::string::npos)
			throw "Wrong config!";
		size_t	size = atoi(splitedLine[1].c_str()) * 1024;
		if (splitedLine[1][splitedLine[1].size() - 1] == 'M')
			size *= 1024;
		_bodySize = size;
		return true;
	}
	if (splitedLine[0] == "allow_methods")
	{
		if (splitedLine.size() < 2)
			throw "Wrong config!";
		for (size_t i = 1; i < splitedLine.size(); i++)
		{
			if (splitedLine[i] != "GET" && splitedLine[i] != "POST" && splitedLine[i] != "DELETE")
				throw "Wrong config!";
			_allowMethods.push_back(splitedLine[i]);
		}
		return true;
	}
	if (splitedLine[0] == "root")
	{
		if (splitedLine.size() != 2)
			throw "Wrong config!";
		_root = splitedLine[1];
		return true;
	}
	if (splitedLine[0] == "index")
	{
		if (splitedLine.size() != 2)
			throw "Wrong config!";
		_index = splitedLine[1];
		return true;
	}
	if (splitedLine[0] == "autoindex")
	{
		if (splitedLine.size() != 2)
			throw "Wrong config!";
		if (splitedLine[1] == "on")
			_autoindex = true;
		else
			_autoindex = false;
		return true;
	}
	if (splitedLine[0] == "return")
	{
		if (splitedLine.size() != 2)
			throw "Wrong config!";
		_redirection = splitedLine[1];
		return true;
	}
	return false;
}
