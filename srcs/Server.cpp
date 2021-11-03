#include "Server.hpp"

Server::Server(int port) :
port(port), timeout(1)
{}

Server::~Server()
{
	for (size_t i = 0; i < connectedUsers.size(); ++i)
	{
		close(connectedUsers[i]->getSockfd());
		delete connectedUsers[i];
	}
	close(sockfd);
}

const int	&Server::getSockfd() const
{
	return (sockfd);
}

void	Server::createSocket()
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		std::cout << "Failed to create socket. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}
}

void	Server::bindSocket()
{
	const int trueFlag = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &trueFlag, sizeof(int)) < 0)
	{
		std::cout << "setsockopt failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	sockaddr.sin_port = htons(port); // htons is necessary to convert a number to network byte order
	if (bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0)
	{
		std::cout << "Failed to bind to port " << port << ". errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}
}

void	Server::listenSocket()
{
	if (listen(sockfd, 128) < 0)
	{
		std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}
	fcntl(sockfd, F_SETFL, O_NONBLOCK);
}

void	Server::grabConnection()
{
	size_t addrlen = sizeof(sockaddr);
	int connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
	if (connection >= 0)
	{
		char	host[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(sockaddr.sin_addr), host, INET_ADDRSTRLEN);
		struct pollfd	pfd;
		pfd.fd = connection;
		pfd.events = POLLIN;
		pfd.revents = 0;
		userFDs.push_back(pfd);
		connectedUsers.push_back(new User(connection));
	}
}
std::string base = "HTTP/1.1 200 OK\nContent-Length: 310\nContent-Type: html\r\n\r\n<!DOCTYPE html>\n<html>\n<head>\n<title>My site</title>\n</head>\n<body>\n<div>\n<p>Nikita, before he became famous!</p>\n</div>\n</body><img src=\"https://sun9-20.userapi.com/impf/wXwTZvFnIjGrztBs9HORaivc44nsoolb1sHZwQ/EbvSGjL-fiU.jpg?size=1371x2048&quality=96&sign=ed8f5582d8ac86f28774ce817f6ac1f3&type=album\">\n</html>\n";
std::string bas = "HTTP/1.1 200 OK\nContent-Length: 49\nContent-Type: image/webp\r\n\r\n/Users/rnancee/Desktop/webs/srcs/favicon.webp";

void	Server::processMessages()
{
	char buf[10240];
	int	pret = poll(userFDs.data(), userFDs.size(), timeout);
	if (pret != 0)
	{
		// Read from the connection
		for (size_t i = 0; i < userFDs.size(); i++)
		{
			if (userFDs[i].revents & POLLIN)
			{
				int q = recv(connectedUsers[i]->getSockfd(), buf, 10240, 0);
				if (q == 0)
				{
					close(connectedUsers[i]->getSockfd());
					connectedUsers.erase(connectedUsers.begin() + i);
					userFDs.erase(userFDs.begin() + i);
					--i;
					continue ;
				}
				buf[q] = 0;
				// if (buf[0] == 'G' || buf[0] == 'D' || buf[0] == 'P')
				// 	Requset Get(buf);

				std::cout << buf << std::endl;
				if (buf[5] == 'f')
				{
					send(connectedUsers[i]->getSockfd(), bas.c_str(), bas.length(), SO_NOSIGPIPE);
				}
				else
					send(connectedUsers[i]->getSockfd(), base.c_str(), base.length(), SO_NOSIGPIPE);
			}
			userFDs[i].revents = 0;
		}
	}
}

int		Server::hadleMessages(User &user)
{
	(void)user;
	return (0);
}