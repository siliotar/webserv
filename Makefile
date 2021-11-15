NAME= webserv

SOURCEFILES=	main.cpp \
				Server.cpp \
				Config.cpp \
				utils.cpp \
				Webserver.cpp \
				ReplyPages.cpp \
				MIME.cpp \
				ServerConfig.cpp \
				Location.cpp \
				Socket.cpp \
				ListenSocket.cpp \
				UserSocket.cpp \
				SocketContainer.cpp \
				Response.cpp \
				Request.cpp

HEADERS=		include/Color.hpp \
				include/Config.hpp \
				include/ListenSocket.hpp \
				include/Location.hpp \
				include/MIME.hpp \
				include/ReplyPages.hpp \
				include/Request.hpp \
				include/Response.hpp \
				include/Server.hpp \
				include/ServerConfig.hpp \
				include/SocketContainer.hpp \
				include/t_listen.hpp \
				include/UserSocket.hpp \
				include/utils.hpp \
				include/Webserver.hpp

SOURCEFOLDER= srcs/

OSOURCEFOLDER= objects/

INCLUDEFOLDER= include/

FLAGS=  -Wall  -Wextra -std=c++98

SOURCE= $(addprefix $(SOURCEFOLDER), $(SOURCEFILES))

OSOURCE= $(addprefix $(OSOURCEFOLDER), $(SOURCEFILES:.cpp=.o))

all: $(NAME)

$(OSOURCEFOLDER):
	mkdir objects
	mkdir objects/commands

$(OSOURCEFOLDER)%.o: $(SOURCEFOLDER)%.cpp
	clang++ $(FLAGS) -c $< -o $@ -I $(INCLUDEFOLDER)

$(NAME): $(OSOURCEFOLDER) $(OSOURCE)
	clang++  $(OSOURCE) -o $(NAME)

clean:
	rm -rf $(OSOURCEFOLDER)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
