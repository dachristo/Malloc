# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dchristo <ybarbier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 11:35:46 by dchristo          #+#    #+#              #
#    Updated: 2017/05/05 16:41:23 by dchristo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = malloc

CC = gcc

#CFLAGS = -Wall -Wextra -Werror

SRC = main2.c malloc.c toolbox.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0m";
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) -o $(NAME) $(OBJS)
	@echo "\033[1;5;1;36m";
	@echo "+---------------------------------------------+";
	@echo "|    _____          .__  .__                  |";
	@echo "|   /     \  _____  |  | |  |   ____   ____   |";
	@echo "|  /  \ /  \ \__  \ |  | |  |  /  _ \_/ ___\  |";
	@echo "| /    Y    \ / __ \|  |_|  |_(  <_> )  \___  |";
	@echo "| \____|__   (____  /____/____/\____/ \___  > |";
	@echo "|          \/     \/                      \/   |";
	@echo "+---------------------------------by dchristo-+";
	@echo "\033[0m";

clean:
	@rm -rf $(OBJS)
	@echo "Clean done"

fclean: clean
	@rm -rf $(NAME)
	@echo "Fclean done"

re: fclean all

.PHONY: clean fclean re all
