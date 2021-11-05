#pragma once

class Socket;

#include <string>
#include <sstream>
#include <sys/socket.h>
#include "Socket.hpp"

class UserSocket : public Socket
{
	private:
		std::string			_message;
		char				_buff[1024];

		UserSocket();
		UserSocket(const UserSocket& copy);
		UserSocket	&operator=(const UserSocket& other);
	public:
		UserSocket(int fd, int port);
		virtual ~UserSocket();
		
		const std::string	&getMessage() const;
		int					readMessage();
};
