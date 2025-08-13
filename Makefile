# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roversch <roversch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/13 10:07:28 by roversch          #+#    #+#              #
#    Updated: 2025/08/13 11:13:48 by roversch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

OBJ_DIR		= obj
SRC_DIR		= source

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC			= main.c utils.c
OBJ			= $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -L. $(MSFLAGS) $(CFLAGS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C fclean
	
re: fclean all

.PHONY: all clean fclean re