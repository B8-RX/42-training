# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 05:11:01 by ssghioua          #+#    #+#              #
#    Updated: 2024/02/06 05:11:05 by ssghioua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/

OBJ_PATH = ./src/obj/

SOURCES = ${SRC_PATH}count_moves.c \
	${SRC_PATH}find_position.c \
	${SRC_PATH}ft_split.c \
	${SRC_PATH}ft_split_utils.c \
	${SRC_PATH}main.c \
	${SRC_PATH}move.c \
	${SRC_PATH}move_utils.c \
	${SRC_PATH}swap.c \
	${SRC_PATH}rotate.c \
	${SRC_PATH}reverse_rotate.c \
	${SRC_PATH}push.c \
	${SRC_PATH}sort.c \
	${SRC_PATH}stack_utils.c \
	${SRC_PATH}update.c \
	${SRC_PATH}init.c \
	${SRC_PATH}check.c \
	${SRC_PATH}free.c \

SOURCES_BONUS = ${SOURCES}

NAME = push_swap.a

LIB_FTPRINTF_DIR = ./src/libs/ft_printf_bonus

LIB_FTPRINTF = ${LIB_FTPRINTF_DIR}/libftprintf.a

CCFLAGS = cc -Wall -Werror -Wextra

HEADER = ${SRC_PATH}include/push_swap.h

OBJECTS = $(patsubst $(SRC_PATH)%.c,$(OBJ_PATH)%.o,$(SOURCES))

OBJECTS_BONUS = $(patsubst $(SRC_PATH)%.c,$(OBJ_PATH)%.o,$(SOURCES_BONUS))

all : ${NAME}

${OBJ_PATH}%.o : ${SRC_PATH}%.c
	@mkdir -p $(@D)
	${CCFLAGS} -I ${HEADER} -c $< -o $@

${NAME} : ${LIB_FTPRINTF} ${HEADER} ${OBJECTS}
	ar -rsc ${NAME} ${OBJECTS} 
	${CCFLAGS} ${NAME} -o push_swap

${LIB_FTPRINTF} :
	make bonus -C ${LIB_FTPRINTF_DIR}
	cp ${LIB_FTPRINTF} ${NAME}

bonus : ${LIB_FTPRINTF} ${HEADER} ${OBJECTS_BONUS}
	ar -rsc ${NAME} ${OBJECTS_BONUS} 
	${CCFLAGS} ${NAME} -o push_swap

clean : 
	rm -f ${OBJECTS}
	cd ${LIB_FTPRINTF_DIR} && make clean

fclean : clean
	rm -f ${NAME} ./push_swap
	cd ${LIB_FTPRINTF_DIR} && make fclean

re : fclean all
