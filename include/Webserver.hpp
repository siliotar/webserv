#pragma once

class Config;
class Server;
class ListenSocket;
class UserSocket;
class SocketContainer;

#include <vector>
#include <poll.h>
#include <csignal>
#include "Server.hpp"
#include "Config.hpp"
#include "ListenSocket.hpp"
#include "UserSocket.hpp"
#include "SocketContainer.hpp"

class Webserver
{
	private:
		std::vector<Server *>		_servers;
		SocketContainer				_sockets;
		const id_t					_timeout;

		Webserver();
		Webserver(const Webserver& copy);
		Webserver	&operator=(const Webserver& other);
	public:
		Webserver(const Config &config);
		virtual ~Webserver();

		void						run();
};
