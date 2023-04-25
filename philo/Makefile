# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboulest <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 16:06:10 by aboulest          #+#    #+#              #
#    Updated: 2023/04/25 16:09:00 by aboulest         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

FILES		= main.c\
			  parsing.c\
			  philo.c\
			  exit.c\
			  initialisation_data.c\
			  mutex.c\
			  action.c\
			  utils.c\
			  eating.c

SRC_DIR		= src/

SRC			= $(addprefix $(SRC_DIR), $(FILES))

OBJ_DIR		= .obj/
OBJ			= $(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))

HEADER		= include/philo.h

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 -pthread
CPPFLAGS	= -I include

RM			= rm -f
DIR_DUP		= mkdir $(OBJ_DIR)
DIR_DUPS	= mkdir $(OBJ_DIR)$(SRC_DIR)

##################################################################

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o:%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR):
	$(DIR_DUP)
	$(DIR_DUPS)

clean: 
	$(RM) $(OBJ)
	rmdir $(OBJ_DIR)$(SRC_DIR)
	rmdir $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
