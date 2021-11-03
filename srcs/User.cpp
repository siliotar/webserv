#include "User.hpp"

User::User(int sockfd) :
_sockfd(sockfd)
{}

User::~User()
{}

int		User::getSockfd() const
{
	return _sockfd;
}

const std::string	&User::getMessage() const
{
	return _message;
}

int		User::readMessage()
{
	std::stringstream	ss;
	int					r;

	while ((r = recv(_sockfd, _buff, sizeof(_buff) - 1, 0)) > 0)
	{
		_buff[r] = 0;
		ss << _buff;
	}
	_message = ss.str();
	if (r == 0 && _message.length() == 0)
		return 0;
	return 1;
}
