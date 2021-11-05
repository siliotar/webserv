#include <string>
#include <vector>
#include <fcntl.h>
#include "User.hpp"
#include "Webserver.hpp"
#include <csignal>
#include "Config.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc < 2)
			throw std::invalid_argument("Usage: ./webserv <config>");

		Config conf(argv[1]);

		Webserver		server(conf);

		server.run();
	}
	catch (std::exception & ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch(const char *err)
	{
		std::cout << err << std::endl;
	}
}