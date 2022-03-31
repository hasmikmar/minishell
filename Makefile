NAME = minishell

SRCS = $(shell find "." -name "*.c")

OBJS = $(SRCS:.c=.o)

LDFLAGS = -L /Users/hmargary/lib
CPPFLAGS = -I /Users/hmargary/include

CC = gcc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME} : ${OBJS}
	${CC} ${CFLAGS} ${CPPFLAGS}   -lreadline -o ${NAME} ${LDFLAGS}  $(OBJS)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
