# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dchristo <ybarbier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 11:35:46 by dchristo          #+#    #+#              #
#    Updated: 2017/03/18 15:48:42 by dchristo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = malloc

PATH_INC = ./libft/

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = main.c malloc.c toolbox.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	@echo "\033[0m";
	$(CC) $(CFLAGS) -I $(PATH_INC) -c $(SRC)
	$(CC) -o $(NAME) $(OBJS) -lm -L libft/ -lft
	@echo "\033[1;5;1;36m";
	@echo "+--------------------------------------------+";
	@echo "|    _____         .__  .__                  |";
	@echo "|   /     \ _____  |  | |  |   ____   ____   |";
	@echo "|  /  \ /  \\__  \ |  | |  |  /  _ \_/ ___\  |";
	@echo "| /    Y    \/ __ \|  |_|  |_(  <_> )  \___  |";
	@echo "| \____|__  (____  /____/____/\____/ \___  > |";
	@echo "|        \/     \/                      \/   |";
	@echo "+--------------------------------by dchristo-+";
	@echo "\033[0m";

clean:
	make -C libft/ clean
	rm -rf $(OBJS)

fclean: clean
	make -C libft/ fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
