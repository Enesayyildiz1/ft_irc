NAME        := ircserv
CC         := c++
FLAGS    :=  -std=c++98 -Wall -Wextra -Werror 

SRCS := main.cpp \
		Server.cpp \
        checkarg.cpp \
		error.cpp \
		Invoker.cpp \
		User.cpp \
		Command.cpp \
		commands/HelpCommand.cpp \
		commands/PassCommand.cpp \
		commands/NickCommand.cpp \
		commands/UserCommand.cpp \
		commands/NoticeCommand.cpp \
		commands/JoinCommand.cpp \
		commands/PrivateMessageCommand.cpp \
		commands/KickCommand.cpp \
		commands/ListCommand.cpp \
		commands/PartCommand.cpp \
		commands/WhoCommand.cpp \
		commands/QuitCommand.cpp \
		channel/Channel.cpp \



OBJS        := ${SRCS:.cpp=.o}

.cpp.o:
	${CC} ${FLAGS} -c $< -o ${<:.cpp=.o}

RM		    := rm -f

${NAME}:	${OBJS}
			${CC} ${FLAGS} -o ${NAME} ${OBJS}

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o

fclean:		clean
			@ ${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re