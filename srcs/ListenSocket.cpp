#include "ListenSocket.hpp"

ListenSocket::ListenSocket(int port)
{
	_port = port;
	createSocket();
	bindSocket();
	listenSocket();
	setNonblock();
}

ListenSocket::~ListenSocket()
{}

void	ListenSocket::createSocket()
{
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd == -1)
	{
		throw "Failed to create socket!";
	}
}

void	ListenSocket::bindSocket()
{
	const int trueFlag = 1;
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &trueFlag, sizeof(int)) < 0)
	{
		throw "setsockopt failed";
	}
	_sockaddr.sin_family = AF_INET;
	_sockaddr.sin_addr.s_addr = INADDR_ANY;
	_sockaddr.sin_port = htons(_port);
	if (bind(_fd, (struct sockaddr*)&_sockaddr, sizeof(_sockaddr)) < 0)
	{
		std::stringstream	ss;
		ss << "Failed to bind to port " << _port << "!";
		throw ss.str().c_str();
	}
}

void	ListenSocket::listenSocket()
{
	if (listen(_fd, 128) < 0)
	{
		throw "Failed to listen on socket!";
	}
}

int		ListenSocket::grabConnection()
{
	size_t addrlen = sizeof(_sockaddr);
	int connection = accept(_fd, (struct sockaddr*)&_sockaddr, (socklen_t*)&addrlen);
	if (connection < 0)
		throw "Failed to accept connection!";
	return connection;
}

bool					ListenSocket::operator==(int fd)
{
	return _fd == fd;
}
