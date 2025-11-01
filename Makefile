# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tonio <tonio@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/10 10:57:37 by tonio             #+#    #+#              #
#    Updated: 2025/11/01 04:08:00 by tonio            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Wextra -g3 -Werror
SRCDIR	= src
MAIN	= main.c
INC		= include
LIBS	= -lreadline

SRC = 	./main.c						\
		./src/builtins/cd.c				\
		./src/builtins/pwd.c			\
		./src/builtins/echo.c			\
		./src/builtins/env.c			\
		./src/builtins/run_builtin.c	\
		./src/parser/parse.c			\
		./src/parser/line_to_tokens.c	\
		./src/parser/tokens_to_cmd.c	\
		./src/parser/tokens_to_cmd_2.c	\
		./src/parser/validate.c			\
		./src/process_env/envify.c		\
		./src/run/heredoc.c 			\
		./src/run/pipeline.c 			\
		./src/run/pipeline2.c 			\
		./src/run/pipeline3.c 			\
		./src/run/redirs.c 				\
		./src/run/run.c 				\
		./src/run/run2.c 				\
		./src/run/run_utils.c 			\
		./src/run/single.c 				\
		./src/shell/shell.c 			\
		./src/shell/shell2.c 			\
		./src/utils/free_arr.c			\
		./src/utils/ft_calloc.c			\
		./src/utils/ft_isalnum.c		\
		./src/utils/ft_itoa.c			\
		./src/utils/ft_memset.c			\
		./src/utils/ft_strjoin.c		\
		./src/utils/ft_strlcpy.c		\
		./src/utils/ft_substr.c			\
		./src/utils/list.c				\
		./src/utils/list2.c				\
		./src/utils/memory.c			\
		./src/utils/path.c				\
		./src/utils/realloc.c			\
		./src/utils/str_to_word_array.c	\
		./src/utils/strings.c			\
		./src/utils/strings2.c			\
		./src/utils/strings3.c			\
		./src/utils/ft_atoi.c			\

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
