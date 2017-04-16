# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldubos <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/27 16:26:37 by ldubos            #+#    #+#              #
#    Updated: 2017/04/16 19:07:41 by dchristo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

FLAGS = -Wall -Werror -Wextra -I . -c

SRCS = $(shell ls -1 | grep "\.c")

OBJS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME): $(OBJS)
	@ar rc  $(NAME) $(OBJS) 
	@ranlib $(NAME)
	@echo "\033[1;5;1;42m \033[0m\c";
	@echo "\033[1;5;1;36m";
	@echo "+---------------------------------------+";
	@echo "|   _      _____ ____  ______ _______   |";
	@echo "|  | |    |_   _|  _ \|  ____|__   __|  |";
	@echo "|  | |      | | | |_) | |__     | |     |";
	@echo "|  | |      | | |  _ <|  __|    | |     |";
	@echo "|  | |____ _| |_| |_) | |       | |     |";
	@echo "|  |______|_____|____/|_|       |_|     |";
	@echo "|                                       |";
	@echo "+--------------------------by dchristo--+";

%.o : %.c
	@$(CC) $(FLAGS) $< -o $@
	@echo "\033[1;5;1;42m \033[0m\c";

clean:	
	@rm -rf $(OBJS)
	@echo "Clean libft done"

fclean:	clean
	@rm -f $(NAME)
	@echo "Fclean libft done"

re:	fclean all

.PHONY: all clean fclean re
