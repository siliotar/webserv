#pragma once

class Server;

#include <string>
#include <time.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <vector>
#include <queue>
#include <set>
#include <sys/socket.h>
#include <algorithm>
#include <fcntl.h>
#include <stdio.h>

class User
{
	private:
		int				_sockfd;
		std::string		_message;
		char			_buff[1024];

		User();
		User(const User& copy);
		User	&operator=(const User& other);
	public:
		User(int sockfd);
		~User();

		// Getters

		int				getSockfd() const;
		const std::string	&getMessage() const;

		// Setters

		
		// Other methods

		int			readMessage();

};

#include "Server.hpp"
