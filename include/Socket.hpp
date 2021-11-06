#pragma once

#include <fcntl.h>

class Socket
{
	protected:
		int			_fd;
		int			_port;
	private:
		Socket(const Socket& copy);
		Socket	&operator=(const Socket& other);
	public:
		Socket();
		virtual ~Socket();

		int						getSockFd() const;
		int						getPort() const;
		void					setNonblock();
};
