# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 01:00:31 by ssghioua          #+#    #+#              #
#    Updated: 2024/08/27 01:00:35 by ssghioua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCE_SERVER = ./server.c

SOURCE_CLIENT = ./client.c

SOURCE_UTILS = ./utils.c

NAME_CLIENT = client

NAME_SERVER = server

HEADER = minitalk.h

INCLUDES = -I./includes/ft_printf/src/lib/

FTPRINTF_DIR = ./includes/ft_printf/

FTPRINTF_LIB = ${FTPRINTF_DIR}libftprintf.a

OBJS_PATH = ./obj/

OBJ_CLIENT = $(patsubst %.c, ${OBJS_PATH}%.o, $(notdir ${SOURCE_CLIENT} ${SOURCE_UTILS}))

OBJ_SERVER = $(patsubst %.c, ${OBJS_PATH}%.o, $(notdir ${SOURCE_SERVER} ${SOURCE_UTILS}))

CC = cc 

CFLAGS = -Wall -Werror -Wextra

all : ${NAME_CLIENT} ${NAME_SERVER}

${OBJS_PATH}%.o : %.c
	mkdir -p ${OBJS_PATH}
	${CC} ${CFLAGS} -I${HEADER} ${INCLUDES} -c $< -o $@

${NAME_SERVER} : ${HEADER} ${FTPRINTF_LIB} ${OBJ_SERVER}
	${CC} ${CFLAGS} -o ${NAME_SERVER} ${OBJ_SERVER} ${FTPRINTF_LIB}

${NAME_CLIENT} : ${HEADER} ${FTPRINTF_LIB} ${OBJ_CLIENT}
	${CC} ${CFLAGS} -o ${NAME_CLIENT} ${OBJ_CLIENT} ${FTPRINTF_LIB}

${FTPRINTF_LIB} :
	@make bonus -C ${FTPRINTF_DIR}

clean :
	rm -rf ${OBJS_PATH}
	@make -C ${FTPRINTF_DIR} clean

fclean: clean
	rm -f ${NAME_SERVER} ${NAME_CLIENT}
	@make -C ${FTPRINTF_DIR} fclean

re : fclean all

.PHONY: all clean fclean
