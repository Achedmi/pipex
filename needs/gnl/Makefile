CC = cc
NAME= get_next_line.a
CFLAGS = -Wall -Wextra -Werror -g
MANDATORY_SRCS= get_next_line.c
MANDATORY_OBJS= get_next_line.o

all: ${NAME}

${NAME}: 
	@${CC} ${CFLAGS} -c ${MANDATORY_SRCS}
	@ar -rcs ${NAME} ${MANDATORY_OBJS}

clean:
	@rm -rf ${MANDATORY_OBJS}