#include "UserSocket.hpp"

UserSocket::UserSocket(int fd, int port)
{
	_fd = fd;
	_port = port;
}

UserSocket::~UserSocket()
{}

const std::string	&UserSocket::getMessage() const
{
	return _message;
}

int		UserSocket::readMessage()
{
	std::stringstream	ss;
	int					r;

	while ((r = recv(_fd, _buff, sizeof(_buff) - 1, 0)) > 0)
	{
		_buff[r] = 0;
		ss << _buff;
	}
	_message = ss.str();
	if (r == 0 && _message.length() == 0)
		return 0;
	return 1;
}
