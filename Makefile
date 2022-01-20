NAME =	pipex.a
SRCS =	src/main.c\
		src/pipex_utiles.c\
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

SRCS_BNS =	src/main_bonus.c\
		src/pipex_utiles_bonus.c\
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
		pipex_utiles.o\
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

OBJS_BNS =	main_bonus.o\
		pipex_utiles_bonus.o\
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
NAME_BONUS = pipex_bonus.a
PROG =	pipex
CC =	gcc
CFLAGS =	-Wall -Wextra -Werror -g

all	:	${NAME}

${NAME} :	${OBJS} ${SRCS}
	ar -rcs ${NAME} ${OBJS}
	${CC} ${NAME} -o ${PROG}

${OBJS} :
	${CC} ${CFLAGS} ${SRCS} -c

clean :
	rm -f ${OBJS}

fclean : clean
	rm -f ${PROG} ${NAME}

re : clean fclean all

bonus : ${NAME_BONUS}

${NAME_BONUS} :	${SRCS_BNS} ${OBJS_BNS}
	ar -rcs ${NAME_BONUS} ${OBJS_BNS}
	${CC} ${NAME_BONUS} -o ${PROG}

${OBJS_BNS} :
	${CC} ${CFLAGS} ${SRCS_BNS} -c

clean_b :
	rm -f ${OBJS_BNS}

fclean_b : clean_b
	rm -f ${PROG} ${NAME_BONUS}


re_b : clean_b fclean_b bonus