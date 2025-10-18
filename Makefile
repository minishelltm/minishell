# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tonio <tonio@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/10 10:57:37 by tonio             #+#    #+#              #
#    Updated: 2025/10/14 15:36:30 by tonio            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Wextra -g3 -Werror
SRCDIR	= src
MAIN	= main.c
INC		= include
LIBS	= -lreadline
SRC		= $(wildcard $(SRCDIR)/*/*.c) $(MAIN)
OBJ		= $(SRC:.c=.o)

TARGET = minishell

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -I./$(INC) $(OBJ) -o $(TARGET) $(LIBS)
%.o:%.c
	$(CC) $(CFLAGS) -I./$(INC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

mclean: all clean

maketests: mclean
	mv $(TARGET) ./tests/

.PHONY: all clean fclean re mclean maketests
