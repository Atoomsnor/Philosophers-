# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roversch <roversch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/13 10:07:28 by roversch          #+#    #+#              #
#    Updated: 2025/09/09 12:57:30 by roversch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= philo

SRC			= main.c init.c monitor.c routine.c reaper.c string_utils.c systime.c
SRC_DIR		= source/ source/utils/
VPATH		= $(SRC_DIR)

OBJ_DIR		= objects/
OBJ			= $(SRC:%.c=$(OBJ_DIR)%.o)

INCLUDES	= include/

CC			= cc
CFLAGS		= -Wall -Wextra -Werror $(addprefix -I,$(INCLUDES)) -g3
DEPFLAGS	= -MMD

all: $(NAME)

$(NAME): $(OBJ) Makefile
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)	

%/:
	mkdir -p $@

$(OBJ_DIR)%.o: %.c Makefile | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $(DEPFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
.PRECIOUS : $(OBJ_DIR)

-include $(OBJ:.o=.d)	