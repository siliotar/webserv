#include "UserSocket.hpp"

UserSocket::UserSocket(int fd, int port)
{
	_fd = fd;
	_port = port;
	setNonblock();
}

UserSocket::~UserSocket()
{}

size_t	UserSocket::completeMessage() const
{
	size_t	pos;
	size_t	lnPos;
	if ((pos = _message.find("\n\n")) != std::string::npos)
	{
		if ((lnPos = _message.find("Content-Length: ")) != std::string::npos)
		{
			size_t	ln = atoi(_message.c_str() + lnPos + 16);
			return ((_message.length() - pos - 2) >= ln) ? ln : 0;
		}
		if (_message.find("\n\n", pos) != std::string::npos)
			return 1;
	}
	return 0;
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
	std::string	t = ss.str();
	if (r == 0 && t.length() == 0)
		return 0;
	_message += ss.str();
	while ((pos = _message.find("\r\n")) != std::string::npos)
		_message.replace(pos, 2, "\n");
	if (_message == "\n\n")
		_message = "";
	size_t	ln;
	while ((ln = completeMessage()))
	{
		if (_message.find("Content-Length: ") != std::string::npos)
			pos = _message.find("\n\n") + 1 + ln;
		else
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
