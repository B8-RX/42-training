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
	${SRC_PATH}find_position_utils.c \
	${SRC_PATH}ft_split.c \
	${SRC_PATH}ft_split_utils.c \
	${SRC_PATH}main.c \
	${SRC_PATH}move.c \
	${SRC_PATH}move_utils.c \
	${SRC_PATH}operations.c \
	${SRC_PATH}sort_utils.c \
	${SRC_PATH}stack_utils.c \
	${SRC_PATH}update_utils.c \

SOURCES_BONUS = ${SOURCES}

NAME = push_swap.a

CCFLAGS = cc -Wall -Werror -Wextra

HEADER = ${SRC_PATH}include/push_swap.h

OBJECTS = $(patsubst $(SRC_PATH)%.c,$(OBJ_PATH)%.o,$(SOURCES))

OBJECTS_BONUS = $(patsubst $(SRC_PATH)%.c,$(OBJ_PATH)%.o,$(SOURCES_BONUS))

all : ${NAME}

${OBJ_PATH}%.o : ${SRC_PATH}%.c
	${CCFLAGS} -I ${HEADER} -c $< -o $@

${NAME} : ${HEADER} ${OBJECTS}
	ar -rsc ${NAME} ${OBJECTS} 
	${CCFLAGS} ${NAME} -o push_swap

bonus : ${HEADER} ${OBJECTS_BONUS}
	ar -rsc ${NAME} ${OBJECTS_BONUS} 
	${CCFLAGS} ${NAME} -o ./push_swap

clean : 
	rm -f ${OBJECTS} 

fclean : clean
	rm -f ${NAME} ./push_swap

re : fclean all
