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

SOURCES = ./src/ft_printf.c ./src/ft_atoi.c ./src/ft_specifier_utils.c ./src/ft_handle_format.c ./src/ft_itoa.c ./src/ft_print_char.c ./src/ft_infill_utils.c ./src/ft_append_utils.c \
./src/ft_print_str.c ./src/ft_print_str_utils.c ./src/ft_printf_utils.c ./src/ft_uitoa.c ./src/ft_ultoa.c ./src/bonus/ft_flags_utils_bonus.c\

SOURCES_BONUS = ${SOURCES}

NAME = libftprintf.a

CCFLAGS = cc -Wall -Werror -Wextra

HEADER = ./src/lib/ft_printf.h

OBJECTS = ${SOURCES:.c=.o}

OBJECTS_BONUS = ${SOURCES_BONUS:.c=.o}

all : ${NAME}

.c.o :
	${CCFLAGS} -I ${HEADER} -c $< -o ${<:.c=.o}

${NAME} : ${HEADER} ${OBJECTS}
	ar -rsc ${NAME} ${OBJECTS}

bonus :  ${HEADER} ${OBJECTS_BONUS}
	ar -rsc ${NAME} ${OBJECTS_BONUS}

clean : 
	rm -f ${OBJECTS}

fclean : clean
	rm -f ${NAME}

re : fclean all
