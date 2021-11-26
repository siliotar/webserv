NAME = webserv

SRCDIR = srcs/

OBJDIR = .obj/

DEPDIR = .dep/

INCLUDEDIR = include/

FLAGS = -Wall -Werror -Wextra -std=c++98

SOURCEFILES =	main.cpp \
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

SOURCE = $(addprefix $(SRCDIR), $(SOURCEFILES))

OBJ = $(addprefix $(OBJDIR), $(SOURCEFILES:.cpp=.o))

DEP = $(addprefix $(DEPDIR), $(SOURCEFILES:.cpp=.d))

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	mkdir -p $(dir $@)
	clang++ $(FLAGS) -c $< -o $@ -I $(INCLUDEDIR) -MMD -MF $(DEPDIR)$*.d

$(OBJDIR):
	mkdir $(OBJDIR)

$(DEPDIR):
	mkdir $(DEPDIR)

$(OBJ): | $(OBJDIR) $(DEPDIR)

$(NAME): $(OBJ)
	clang++  $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJDIR) $(DEPDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all

-include $(DEP)
