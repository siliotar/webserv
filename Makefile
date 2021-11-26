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
				Request.cpp \
				c_function.cpp

SOURCE = $(addprefix $(SRCDIR), $(SOURCEFILES))

OBJ = $(addprefix $(OBJDIR), $(SOURCEFILES:.cpp=.o))

DEP = $(addprefix $(DEPDIR), $(SOURCEFILES:.cpp=.d))

all: $(NAME)

$(DEPDIR)%.d: $(SRCDIR)%.cpp
	mkdir -p $(dir $@)
	clang++ -MT $(<:$(SRCDIR)%.cpp=$(OBJDIR)%.o) -MM $< > $@ -I $(INCLUDEDIR)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	mkdir -p $(dir $@)
	clang++ $(FLAGS) -c $< -o $@ -I $(INCLUDEDIR)

$(NAME): $(DEP) $(OBJ)
	clang++  $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJDIR) $(DEPDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all

q:
	clang++ www/test.cpp -o www/a.out
	clang++ www/test_mulicgi.cpp -o www/test_cgi_my

-include $(DEP)
