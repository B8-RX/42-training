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

SOURCES = ${wildcard ${SRC_PATH}*.c} 

SOURCES_BONUS = ${SOURCES}

NAME = push_swap.a

EXE = run_test.out

CCFLAGS = cc -Wall -Werror -Wextra

HEADER = ${SRC_PATH}include/push_swap.h

OBJECTS = $(patsubst $(SRC_PATH)%.c,$(OBJ_PATH)%.o,$(SOURCES))

OBJECTS_BONUS = $(patsubst $(SRC_PATH)%.c,$(OBJ_PATH)%.o,$(SOURCES_BONUS))

all : ${NAME}

${OBJ_PATH}%.o : ${SRC_PATH}%.c
	${CCFLAGS} -I ${HEADER} -c $< -o $@

${NAME} : ${HEADER} ${OBJECTS}
	ar -rsc ${NAME} ${OBJECTS} 
	${CCFLAGS} ${NAME} -o ${EXE}

bonus : ${HEADER} ${OBJECTS_BONUS}
	ar -rsc ${NAME} ${OBJECTS_BONUS} 
	${CCFLAGS} ${NAME} -o ${EXE}

clean : 
	rm -f ${OBJECTS} 

fclean : clean
	rm -f ${NAME} ./${EXE}

re : fclean all
