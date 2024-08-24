# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/17 09:46:57 by ssghioua          #+#    #+#              #
#    Updated: 2024/07/17 09:46:58 by ssghioua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -I./mlx -Iincludes/libft 
	MLX_FLAGS = -L./mlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
	INCLUDES = -I/opt/X11/include -I./mlx -Iincludes/libft
	MLX_FLAGS = -L./mlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif
 
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a

HEADER = ./so_long.h

LIBFT_DIR = ./includes/libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a

OBJS_PATH = ./objs/

SOURCE = ./main.c ./display.c ./display_utils-1.c ./display_utils-2.c ./events.c ./moves_utils.c ./free_utils.c ./free_img.c ./init.c ./init_2.c ./check_utils.c ./map_checking.c ./map_checking_utils.c ./map_utils.c ./path_checking.c ./errors_utils.c 

OBJS = $(patsubst %.c, ${OBJS_PATH}%.o, $(notdir ${SOURCE}))

NAME = minilibx_test

CFLAGS = -Wall -Werror -Wextra -g3

CC = cc

all: $(NAME)
 
$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(LIBFT_LIB)
${OBJS_PATH}%.o : %.c
	mkdir -p ${OBJS_PATH}
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES) -I$(HEADER)
 
$(MLX_LIB):
	@make -C $(MLX_DIR) --no-print-directory

$(LIBFT_LIB): 
	@make bonus -C $(LIBFT_DIR)
	cp $(LIBFT_LIB) $(NAME)

clean: 
	rm -rf ${OBJS_PATH}
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f ${NAME}
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY : all clean fclean re libft mlx
