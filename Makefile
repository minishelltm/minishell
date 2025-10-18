# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmicael <mmicael@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/10 10:57:37 by tonio             #+#    #+#              #
#    Updated: 2025/10/18 03:24:05 by mmicael          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -g3 -I./include -Werror
SRC = 	./main.c						\
		./src/utils/strings.c			\
		./src/utils/strings_utils.c     \
		./src/utils/strings2.c			\
		./src/utils/path.c				\
		./src/utils/list.c				\
		./src/utils/list2.c				\
		./src/utils/realloc.c			\
		./src/process_env/envify.c		\
		./src/utils/str_to_word_array.c	\
		./src/shell/shell.c 			\
		./src/shell/find_bin.c 			\
		./src/run/run.c					\
		./src/builtins/run_builtin.c	\
		./src/builtins/cd.c				\
		./src/parser/parse.c			\

OBJ = $(SRC:.c=.o)

TARGET = minishell

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

mclean: all clean

maketests: mclean
	mv $(TARGET) ./tests/

.PHONY: all clean fclean re mclean maketests
