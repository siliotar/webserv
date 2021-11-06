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

void	Webserver::run()
{
	signal(SIGINT, sigHandler);
	while (work)
	{
		int	pret = poll(_sockets.getPollfds().data(), _sockets.getPollfds().size(), _timeout);
		if (pret != 0)
		{
			for (size_t i = 0; i < _sockets.getPollfds().size(); ++i)
			{
				if (_sockets.getPollfds()[i].revents & POLLIN)
				{
					if (ListenSocket *lis = dynamic_cast<ListenSocket*>(_sockets.getSockets()[i]))
					{
						_sockets.add(new UserSocket(lis->grabConnection(), lis->getPort()));
						break;
					}
					UserSocket	*user = dynamic_cast<UserSocket*>(_sockets.getSockets()[i]);
					user->getPort();
					
					if (!user->readMessage())
					{
						_sockets.remove(i);
						--i;
						continue ;
					}
					Response response_user(user->getMessage(), *(_servers[0]));
					ReplyPages reply;
					reply.setReplyBody(200, response_user.getResponse(), "text/html");
					send(user->getSockFd(), reply.getReply(200).c_str(), reply.getReply(200).size(), 0);
					std::cout << user->getMessage() << std::endl;
				}
				_sockets.getPollfds()[i].revents = 0;
			}
		}
	}
}
