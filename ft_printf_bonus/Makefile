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

SOURCES = ./src/mandatory/ft_printf.c ./src/mandatory/ft_handle_format.c ./src/mandatory/ft_print_utils.c \

SOURCES_BONUS = ./src/bonus/ft_printf_bonus.c ./src/bonus/ft_atoi_bonus.c ./src/bonus/ft_flags_utils_bonus.c ./src/bonus/ft_specifier_utils_bonus.c ./src/bonus/ft_handle_format_bonus.c ./src/bonus/ft_itoa_bonus.c ./src/bonus/ft_print_char_bonus.c \
./src/bonus/ft_print_str_bonus.c ./src/bonus/ft_print_utils_bonus.c ./src/bonus/ft_printf_utils_bonus.c ./src/bonus/ft_uitoa_bonus.c ./src/bonus/ft_ultoa_bonus.c\

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
