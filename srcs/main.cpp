#include <string>
#include <vector>
#include <fcntl.h>
#include "User.hpp"
#include "Server.hpp"
#include <csignal>

bool	work = true;

void	sigHandler(int signum)
{
	(void)signum;
	work = false;
}

int main(int argc, char **argv)
{
	try {
		if (argc < 2)
			throw std::invalid_argument("Usage: ./webserv <port>");
		int port = atoi(argv[1]);

		if (port < 1024 || port > 49151)
			throw std::invalid_argument("Wrong port!");

		Server		server(port);

		// Create a socket (IPv4(AF_INET), TCP)
		server.createSocket();

		// Listen to port on any address
		server.bindSocket();

		// Start listening.
		server.listenSocket();

		fcntl(server.getSockfd(), F_SETFL, O_NONBLOCK);

		signal(SIGINT, sigHandler);

		while (work)
		{
			// Grab a connection from the queue
			server.grabConnection();

			server.processMessages();
		}
	}
	catch (std::exception & ex)
	{
		std::cout << ex.what() << std::endl;
	}
}