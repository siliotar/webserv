#pragma once

class Socket;

#include <vector>
#include <poll.h>
#include <unistd.h>
#include <stddef.h>
#include "Socket.hpp"

typedef struct		s_sockdata
{
	s_sockdata(Socket *sock, struct pollfd *pollfd) :
	socket(sock), pollfd(pollfd) {}
	Socket			*socket;
	struct pollfd	*pollfd;
}					sockdata;

class SocketContainer
{
	private:
		std::vector<Socket *>		_sockets;
		std::vector<struct pollfd>	_pollfds;

		SocketContainer(const SocketContainer& copy);
		SocketContainer	&operator=(const SocketContainer& other);
	public:
		SocketContainer();
		virtual ~SocketContainer();

		void						add(Socket *socket);
		void						remove(size_t idx);
		std::vector<Socket *>		&getSockets();
		std::vector<struct pollfd>	&getPollfds();
		size_t						size() const;

		sockdata					operator[](size_t n);
};
