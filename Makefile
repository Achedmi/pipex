VPATH= mandatory_objects mandatory bonus bonus_objects
CFLAGS = -Wall -Wextra -Werror -g
CC = cc
NAME = pipex.a
PROG = pipex
MANDATORY_OBJS_PATH=./mandatory_objects/
MANDATORY_OBJS_DIRETORY=mandatory_objects

MANDATORY_SRCS= pipex.c\
				pipex_utiles.c

MANDATORY_OBJS= pipex.o\
				pipex_utiles.o

MANDATORY_HEADER= pipex.h

all:${MANDATORY_OBJS_DIRETORY} ${NAME}

${NAME}: ${MANDATORY_OBJS} ${MANDATORY_SRCS}
	@make -C ./needs/libft
	@make clean -C ./needs/libft
	@mv ./needs/libft/libft.a ./
	@make -C ./needs/gnl
	@make clean -C ./needs/gnl
	@mv ./needs/gnl/get_next_line.a ./
	ar -rcs ${NAME} $(addprefix ${MANDATORY_OBJS_PATH},${MANDATORY_OBJS})
	${CC} ${NAME} get_next_line.a libft.a -o ${PROG}

%.o : ./mandatory/%.c $(MANDATORY_HEADER)
	${CC} ${CFLAGS} -c $< -o ${MANDATORY_OBJS_PATH}$@

${MANDATORY_OBJS_DIRETORY}: 
	mkdir -p $@

re: fclean all

fclean: clean
	rm -rf *.a pipex
	@make clean -C ./needs/libft
	@make clean -C ./needs/gnl

clean:
	rm -rf ${MANDATORY_OBJS_DIRETORY}

#-------------------------------------------------------------------------#
#								Bonus Part								  #
#-------------------------------------------------------------------------#

BONUS_SRCS= pipex_bonus.c\
				pipex_utiles_bonus.c

BONUS_OBJS= pipex_bonus.o\
				pipex_utiles_bonus.o

NAME_BONUS= pipex_bonus.a
PROG_BONUS= checker
BONUS_HEADER= pipex_bonus.h
BONUS_OBJS_PATH=./bonus_objects/
BONUS_OBJS_DIRETORY=bonus_objects

bonus: ${BONUS_OBJS_DIRETORY} ${NAME_BONUS}

${NAME_BONUS}: ${BONUS_OBJS} ${BONUS_SRCS}
	@make -C ./needs/libft
	@make clean -C ./needs/libft
	@mv ./needs/libft/libft.a ./
	@make -C ./needs/gnl
	@make clean -C ./needs/gnl
	@mv ./needs/gnl/get_next_line.a ./
	ar -rcs ${NAME_BONUS} $(addprefix ${BONUS_OBJS_PATH},${BONUS_OBJS})
	${CC} ${NAME_BONUS} get_next_line.a libft.a -o ${PROG_BONUS}	

%.o: ./bonus/%.c ${BONUS_HEADER}
	${CC} ${CFLAGS} -c $< -o ${BONUS_OBJS_PATH}$@

${BONUS_OBJS_DIRETORY}:
	mkdir -p $@

re_bonus: fclean_bonus bonus

fclean_bonus: clean_bonus
	rm -rf *.a ${PROG_BONUS}
	@make clean -C ./needs/libft
	@make clean -C ./needs/gnl

clean_bonus:
	rm -rf ${BONUS_OBJS_DIRETORY}


test1:
	./pipex txt.txt ls ls txt7.txt

test2:
	./pipex txt.txt ls ls ls ls txt7.txt