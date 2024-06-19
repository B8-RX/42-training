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

SOURCES = ${SRC_PATH}ft_printf.c ${SRC_PATH}ft_atoi_free.c ${SRC_PATH}ft_specifier_utils.c ${SRC_PATH}ft_handle_format.c ${SRC_PATH}ft_itoa.c ${SRC_PATH}ft_print_char.c ${SRC_PATH}ft_infill_utils.c ${SRC_PATH}ft_append_utils.c \
${SRC_PATH}ft_print_str.c ${SRC_PATH}ft_print_str_utils.c ${SRC_PATH}ft_printf_utils.c ${SRC_PATH}ft_uitoa.c ${SRC_PATH}ft_ultoa.c ${SRC_PATH}ft_flags_utils_bonus.c\

SOURCES_BONUS = ${SOURCES}

NAME = libftprintf.a

CCFLAGS = cc -Wall -Werror -Wextra

HEADER = ./src/lib/ft_printf.h

OBJECTS = $(patsubst $(SRC_PATH)%.c,$(OBJ_PATH)%.o,$(SOURCES))

OBJECTS_BONUS = $(patsubst $(SRC_PATH)%.c,$(OBJ_PATH)%.o,$(SOURCES_BONUS))

LIBFT_DIR = ../libft

LIBFT = ${LIBFT_DIR}/libft.a

all : ${NAME}

${OBJ_PATH}%.o : ${SRC_PATH}%.c
	${CCFLAGS} -I ${HEADER} -c $< -o $@

${NAME} : ${LIBFT} ${HEADER} ${OBJECTS}
	ar -rsc ${NAME} ${OBJECTS}

${LIBFT} :
	make bonus -C ${LIBFT_DIR}
	cp ${LIBFT} ${NAME}

bonus : ${LIBFT} ${HEADER} ${OBJECTS_BONUS}
	ar -rsc ${NAME} ${OBJECTS_BONUS}

clean : 
	rm -f ${OBJECTS}
	cd ${LIBFT_DIR} && make clean

fclean : clean
	rm -f ${NAME}
	cd ${LIBFT_DIR} && make fclean

re : fclean all
