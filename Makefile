NAME =	pipex.a
SRCS =	src/main.c\
		needs/gnl/get_next_line.c\
		needs/libft/ft_strlen.c\
		needs/libft/ft_strlcat.c\
		needs/libft/ft_split.c\
		needs/libft/ft_substr.c\
		needs/libft/ft_strjoin.c\
		needs/libft/ft_calloc.c\
		needs/libft/ft_strlcpy.c\
		needs/libft/ft_bzero.c\
		needs/libft/ft_memmove.c\
		needs/libft/ft_strncmp.c
OBJS =	main.o\
		get_next_line.o\
		ft_strlen.o\
		ft_strlcat.o\
		ft_split.o\
		ft_substr.o\
		ft_strjoin.o\
		ft_calloc.o\
		ft_strlcpy.o\
		ft_bzero.o\
		ft_memmove.o\
		ft_strncmp.o
NAME =	pipex.a
PROG =	pipex
CC =	gcc
CFLAGS =	-Wall -Wextra -Werror -g

all	:	${NAME}

${NAME} :	${OBJS}
	ar -rcs ${NAME} ${OBJS}
	${CC} ${NAME} -o ${PROG}

${OBJS} :
	${CC} ${CFLAGS} ${SRCS} -c

clean :
	rm -f ${OBJS}

fclean : clean
	rm -f ${PROG} ${NAME}

re : clean fclean all

#need to add bonus part