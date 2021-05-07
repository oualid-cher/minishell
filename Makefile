# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/13 14:28:23 by ahmcherk          #+#    #+#              #
#    Updated: 2020/01/07 23:29:41 by ahmcherk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC =	builtin.c builtin1.c cmd_manager.c ft_cd.c ft_readinit.c\
		main.c readline.c readline_tools.c tools.c tools2.c vartools.c\
		ft_tools.c
FLAGS = -Wall -Werror -Wextra
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	make -C libft
	gcc -ggdb3 $(FLAGS) -c $(SRC)
	gcc -o $(NAME) $(OBJ) ./libft/libft.a

clean :
	rm -rf $(OBJ)
	make clean -C libft

fclean : clean
	rm -rf $(NAME)
	make fclean -C libft

re : fclean all
