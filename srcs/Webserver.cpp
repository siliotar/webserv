#include "Webserver.hpp"

bool	work = true;

void	sigHandler(int signum)
{
	(void)signum;
	work = false;
}

Webserver::Webserver(const Config &config) :
_timeout(1)
{
	std::set<int>	ports;
	for (size_t i = 0; i < config.getServers().size(); ++i)
		_servers.push_back(new Server(*(config.getServers()[i])));
	for (size_t i = 0; i < _servers.size(); ++i)
		ports.insert(_servers[i]->getPorts().begin(), _servers[i]->getPorts().end());
	std::set<int>::iterator	it = ports.begin();
	for (; it != ports.end(); ++it)
		_sockets.add(new ListenSocket(*it));
}

Webserver::~Webserver()
{
	for (size_t i = 0; i < _servers.size(); ++i)
		delete _servers[i];
}

Server	*Webserver::defineServer(const std::string &msg, int port)
{
	size_t	pos;
	if ((pos = msg.find("Host: ")) == std::string::npos)
		return 0;
	std::istringstream	ss(msg.substr(pos));
	std::string		host;
	ss >> host >> host;
	std::vector<Server *>	candidates;
	for (size_t i = 0; i < _servers.size(); i++)
		if (_servers[i]->isListen(port))
			candidates.push_back(_servers[i]);
	for (size_t i = 0; i < candidates.size(); i++)
		if (candidates[i]->containsName(host))
			return candidates[i];
	return candidates[0];
}

void	Webserver::run()
{
	signal(SIGINT, sigHandler);
	while (work)
	{
		int	pret = poll(_sockets.getPollfds().data(), _sockets.getPollfds().size(), _timeout);
		if (pret != 0)
		{
			for (size_t i = 0; i < _sockets.size(); ++i)
			{
				if (_sockets[i].pollfd->revents & POLLIN)
				{
					if (ListenSocket *lis = dynamic_cast<ListenSocket*>(_sockets[i].socket))
					{
						_sockets.add(new UserSocket(lis->grabConnection(), lis->getPort()));
						break;
					}
					UserSocket	*user = dynamic_cast<UserSocket*>(_sockets[i].socket);
					if (!user->readMessage())
					{
						_sockets.remove(i);
						--i;
						continue ;
					}
					// try {
					// std::cout << user->getMessage() << std::endl;
					Response response_user(user->getMessage(), defineServer(user->getMessage(), _sockets[i].socket->getPort()));
					send(user->getSockFd(), response_user.getResponse().c_str(), response_user.getResponse().size(), 0);
					// }
					// catch (char * str) {
					// 	send(user->getSockFd(), )
					// }
					// Server	*s = defineServer(user->getMessage(), _sockets[i].socket->getPort());
					// const Location	*loc = s->getLocation("/images");
					// std::cout << loc->getRoot() << std::endl;
				}
				_sockets[i].pollfd->revents = 0;
			}
		}
	}
}
