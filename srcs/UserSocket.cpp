#include "UserSocket.hpp"

UserSocket::UserSocket(int fd, int port)
{
	_fd = fd;
	_port = port;
	setNonblock();
}

UserSocket::~UserSocket()
{}

bool	UserSocket::completeMessage() const
{
	size_t	pos;
	if ((pos = _message.find("\n\n")) != std::string::npos)
		if (_message.find("\n\n", pos) != std::string::npos)
			return true;
	return false;
}

std::string	UserSocket::popMessage()
{
	std::string	ret = _msgQueue.front();
	_msgQueue.pop();
	return ret;
}

int		UserSocket::readMessage()
{
	std::stringstream	ss;
	int					r;
	size_t				pos;

	while ((r = recv(_fd, _buff, sizeof(_buff) - 1, 0)) > 0)
	{
		_buff[r] = 0;
		ss << _buff;
	}
	if (r == 0 && ss.str().length() == 0)
		return 0;
	_message += ss.str();
	while ((pos = _message.find("\r\n")) != std::string::npos)
		_message.replace(pos, 2, "\n");
	while (completeMessage())
	{
		pos = _message.find("\n\n", _message.find("\n\n"));
		_msgQueue.push(_message.substr(0, pos + 1));
		_message.erase(0, pos + 2);
	}
	return 1;
}

bool	UserSocket::readyToResponse() const
{
	return _msgQueue.size() > 0;
}

void	UserSocket::clearMessage()
{
	_message.clear();
}
