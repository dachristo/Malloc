# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dchristo <ybarbier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 11:35:46 by dchristo          #+#    #+#              #
#    Updated: 2017/05/23 14:21:44 by dchristo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

LS = libft_malloc.so

CC = gcc

CFLAGS = -Wall -Wextra -Werror -W

SRCDIR = src

CFILES = malloc.c realloc.c free.c show_alloc_mem.c\
		toolbox.c toolbox2.c libft.c

SRC = $(patsubst %, $(SRCDIR)/%, $(CFILES))

NORMINETTE = $(shell norminette $(SRC))

OBJS = $(SRC:.c=.o)

all: $(NAME)


$(NAME): $(OBJS)
	@echo "\033[0m";
	$(CC) $(CFLAGS) $(OBJS) -shared -o $(NAME)
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

norm:
	@echo $(NORMINETTE)

clean:
	@rm -rf $(OBJS)
	@echo "Clean done"

fclean: clean
	@rm -rf $(NAME) $(LS)
	@echo "Fclean done"

re: fclean all

%.o: %.c
			$(CC) -c $< $(CFLAGS) -o $@

.PHONY: clean fclean re all norminette
