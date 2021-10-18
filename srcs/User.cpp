#include "User.hpp"

User::User(int sockfd) :
sockfd(sockfd)
{}

User::~User()
{}

int		User::getSockfd() const
{
	return sockfd;
}
