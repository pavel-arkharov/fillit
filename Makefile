# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/27 16:11:40 by parkharo          #+#    #+#              #
#    Updated: 2022/01/11 17:34:47 by tpolonen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I ./code/

NAME = fillit

SRC = ./code

SRCS  = $(SRC)/backtrack.c
SRCS += $(SRC)/bits.c
SRCS += $(SRC)/blocks.c
SRCS += $(SRC)/field.c
SRCS += $(SRC)/main.c
SRCS += $(SRC)/print.c
SRCS += $(SRC)/validate.c

SRC2 = $(SRC:%.c=%.o)

$(NAME): $(SRCS)
	@make -C ./libft fclean && make -C ./libft
	@echo "Compiling fillit..."
	@$(CC) $(CFLAGS) $(SRCS) -L./libft -lft -o $(NAME)
	@echo "OK!"
	
clean: 
	@make -C ./libft clean
	@echo "Removing fillit .o files..."
	@/bin/rm -f *.o
	@echo "OK!"

fclean: clean
	@make -C ./libft fclean
	@echo "Cleaning up fillit..."
	@/bin/rm -f $(NAME)
	@echo "OK!"

all: $(NAME)

re: fclean all
	@echo "Re-compiling..."
	@echo "OK!"
