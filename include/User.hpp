#pragma once

class Server;
class Message;
class Channel;

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
#include "Server.hpp"

class User
{
	private:
		int									sockfd;

		User();
		User(const User& copy);
		User	&operator=(const User& other);
	public:
		User(int sockfd);
		~User();

		// Getters

		int									getSockfd() const;

		// Setters

		
		// Other methods

};
