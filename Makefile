# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 17:57:32 by hbenazza          #+#    #+#              #
#    Updated: 2024/08/01 21:10:39 by tkoulal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = ./program/main.c\
	./program/reading_promp.c \
	./parse/parse.c\
	./parse/lexer.c\
	./parse/tokens.c\
	./libft/ft_atoi.c\
	./libft/ft_lstadd_back.c \
	./libft/ft_lstadd_front.c \
	./libft/ft_lstsize.c \
	./libft/ft_lstnew.c	\
	./libft/ft_split.c \
	./libft/ft_strdup.c \
	./libft/ft_strjoin.c \
	./libft/ft_strlen.c \
	./libft/ft_substr.c \
	./libft/ft_strncmp.c\
	./libft/ft_strtrim.c\
	./libft/ft_strchr.c\
	./execution/herdoc.c\
	./execution/main.execuction.c\
	./execution/execution.c\
	./execution/check_built_in.c\
	./execution/clean_up.c\
	./execution/exec_utils.c\
	./execution/handel_files.c\
	./built-in/commands1.c\
	./parse/init_struct.c\
	./parse/quotes.c\
	./parse/tools.c\
	./expander/expander.c\
	./parse/tokens_utils.c\
	./parse/redirections.c\
	./parse/signals.c\
	./expander/expander_tools.c\
	./libft/ft_itoa.c\
	./libft/ft_calloc.c\
	./expander/envirements.c\
	./expander/lenght_envirements.c\
	./libft/ft_deletenode.c\
	./built-in/commands2.c\
	./built-in/commands_utils.c\
	./built-in/commands_utils2.c\
	./parse/spaces.c\
	./parse/utils.c

OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

%.o: %.c
	cc $(CFLAGS) -c -o $@ $^

all: $(NAME)
$(NAME): $(SRC) $(OBJ)
	@cc $(CFLAGS) -lreadline  $(OBJ) -o $(NAME)
	@echo "ready!"

clean:
	@rm -rf $(OBJ)
	@echo "objects removed!"

fclean:
	@rm -rf $(OBJ) $(NAME)
	@echo "objects and executable removed!"

re:fclean $(NAME)

.SECONDARY : OBJ
