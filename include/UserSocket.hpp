#pragma once

class Socket;

#include <string>
#include <sstream>
#include <queue>
#include <sys/socket.h>
#include <cstdlib>
#include "Socket.hpp"

class UserSocket : public Socket
{
	private:
		std::string				_message;
		char					_buff[1024];
		std::queue<std::string>	_msgQueue;

		UserSocket();
		UserSocket(const UserSocket& copy);
		UserSocket	&operator=(const UserSocket& other);

		size_t				completeMessage() const;
	public:
		UserSocket(int fd, int port);
		virtual ~UserSocket();
		
		std::string			popMessage();
		int					readMessage();
		bool				readyToResponse() const;
		void				clearMessage();
};
