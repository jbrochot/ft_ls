# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ezonda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/21 11:32:21 by ezonda            #+#    #+#              #
#    Updated: 2019/04/03 16:19:28 by ezonda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = srcs/main.c srcs/parser.c srcs/tools/tools.c srcs/tools/tools_parser.c \
	  srcs/print_ls.c srcs/ascii.c srcs/time.c srcs/long.c srcs/recursive.c \
	  srcs/tools/tools_time.c srcs/tools/tools_time2.c srcs/multi_path.c \
	  srcs/tools/tools_multi_path.c srcs/tools/tools_long.c \
	  srcs/tools/tools_multi_path2.c srcs/tools/tools_display.c

OBJ = $(SRC: .c=.o)

LIB = libft/libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	@echo "Compilation..."
	@$(CC) $(FLAGS) $(LIB) -I./libft $(OBJ) -I./includes -o $(NAME)
	@echo "OK."

$(LIB):
	@make -C libft/ fclean
	@make -C libft/

%.o: %.c
	$(CC) -o $@ -c $< -I./includes

clean:
	@echo "Deleting all object file ..."
	@make -C libft/ clean
	@echo "OK."

fclean:
	@echo "Deleting ./ft_ls"
	@make -C libft/ fclean
	@rm -rf $(NAME)
	@echo "OK."

re: fclean all

.PHONY: clean fclean re all
