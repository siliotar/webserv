#pragma once

class Config;

class Webserver
{
	private:
		Webserver();
		Webserver(const Webserver& copy);
		Webserver	&operator=(const Webserver& other);
	public:
		Webserver(const Config &config);
		virtual ~Webserver();
};

#include "Config.hpp"
