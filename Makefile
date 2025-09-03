# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roversch <roversch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/13 10:07:28 by roversch          #+#    #+#              #
#    Updated: 2025/09/03 17:19:01 by roversch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC		= main.c init.c monitor.c routine.c reaper.c string_utils.c systime.c
SRC_DIR	= source/ source/utils/
VPATH	= $(SRC_DIR)

DEP_DIR		= dependencies/
DEPFLAGS	= -MM -MF $@ -MT $@ -MT $(OBJ_DIR)$(addsuffix .o,$(notdir $(basename $<)))

OBJ		= $(SRC:%.c=$(OBJ_DIR)%.o)
OBJ_DIR	= objects/

INCLUDES = include/

CC = cc
CFLAGS = -Wall -Wextra -Werror $(addprefix -I,. $(INCLUDES))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

include $(addprefix $(DEP_DIR), $(SRC:%.c=%.d))

%/:
	mkdir -p $@

$(DEP_DIR)%.d : %.c | $(DEP_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEPFLAGS) $<

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(DEP_DIR)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
.PRECIOUS : $(OBJ_DIR) $(DEP_DIR)