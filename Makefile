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

SOURCEFOLDER= srcs/

OSOURCEFOLDER= objects/

INCLUDEFOLDER= include/

FLAGS=  -Wall -Werror -Wextra -std=c++98

SOURCE= $(addprefix $(SOURCEFOLDER), $(SOURCEFILES))

OSOURCE= $(addprefix $(OSOURCEFOLDER), $(SOURCEFILES:.cpp=.o))

all: $(NAME)

$(OSOURCEFOLDER):
	mkdir objects
	mkdir objects/commands

$(OSOURCEFOLDER)%.o: $(SOURCEFOLDER)%.cpp
	clang++ $(FLAGS) -c $< -o $@ -I $(INCLUDEFOLDER)

$(NAME): $(OSOURCEFOLDER) $(OSOURCE)
	clang++ $(OSOURCE) -o $(NAME)

test:
	mkdir YoupiBanane
	touch YoupiBanane/youpi.bad_extension
	touch YoupiBanane/youpi.bla
	mkdir YoupiBanane/nop
	touch YoupiBanane/nop/youpi.bad_extension
	touch YoupiBanane/nop/youpi.bla
	mkdir YoupiBanane/Yeah
	touch YoupiBanane/Yeah/not_happy.bad_extension

cleantest:
	rm -rf YoupiBanane

clean:
	rm -rf $(OSOURCEFOLDER)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
