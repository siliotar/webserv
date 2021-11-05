#pragma once

typedef struct s_listen
{
	unsigned int	inaddr;
	unsigned int	port;
	s_listen(unsigned int addr, unsigned int port)
	: inaddr(addr), port(port)
	{}
}t_listen;
