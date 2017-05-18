# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dchristo <ybarbier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 11:35:46 by dchristo          #+#    #+#              #
#    Updated: 2017/05/18 18:25:04 by dchristo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

LS = libft_malloc.so

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = malloc.c toolbox.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0m";
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) -shared -o $(NAME) $(OBJS)
	ln -s $(NAME) $(LS)
	@echo "\033[1;5;1;36m";
	@echo "+---------------------------------------------+";
	@echo "|    _____          .__  .__                  |";
	@echo "|   /     \  _____  |  | |  |   ____   ____   |";
	@echo "|  /  \ /  \ \__  \ |  | |  |  /  _ \_/ ___\  |";
	@echo "| /    Y    \ / __ \|  |_|  |_(  <_> )  \___  |";
	@echo "| \____|__   (____  /____/____/\____/ \___  > |";
	@echo "|          \/     \/                      \/  |";
	@echo "+---------------------------------by dchristo-+";
	@echo "\033[0m";

main:
	$(CC) main2.c -o main_malloc

clean:
	@rm -rf $(OBJS)
	@echo "Clean done"

fclean: clean
	@rm -rf $(NAME) $(LS) main_malloc
	@echo "Fclean done"

re: fclean all

.PHONY: clean fclean re all
