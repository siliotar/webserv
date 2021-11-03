#pragma once

class User;
class Channel;
class UserInfo;
class History;

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <poll.h>
#include <fstream>
#include <string>
#include <map>
#include "User.hpp"
// #include "Request.hpp"

#define	DISCONNECT	-2

typedef  int (Server::*Method) (const Message &, User &);

class Server
{
	private:
		int										port;
		std::vector<User *>						connectedUsers;
		std::vector<struct pollfd>				userFDs;
		int										sockfd;
		sockaddr_in								sockaddr;
		const id_t								timeout;

		Server();
		Server(const Server& copy);
		Server	&operator=(const Server& other);

	public:
		Server(int port);
		~Server();

		// Getters

		const int								&getSockfd() const;

		// Server setup

		void									createSocket();
		void									bindSocket();
		void									listenSocket();
		void									grabConnection();
		void									processMessages();
		int										hadleMessages(User &user);
};
