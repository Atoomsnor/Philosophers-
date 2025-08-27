# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roversch <roversch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/13 10:07:28 by roversch          #+#    #+#              #
#    Updated: 2025/08/27 14:01:30 by roversch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC		= main.c init.c monitor.c routine.c utils.c print_message.c
SRC_DIR	= source


OBJ		= $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR	= objects

CC = cc
CFLAGS = -Wall -Wextra -Werror


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re