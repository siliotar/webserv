#include "Socket.hpp"

Socket::Socket()
{}

Socket::~Socket()
{}

int		Socket::getSockFd() const
{
	return _fd;
}

int		Socket::getPort() const
{
	return _port;
}

void	Socket::setNonblock()
{
	fcntl(_fd, F_SETFL, O_NONBLOCK);
}
