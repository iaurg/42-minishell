# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/27 18:38:37 by mfrasson          #+#    #+#              #
#    Updated: 2021/12/04 20:53:04 by itaureli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	src/main.c 

OBJ		=	${SRC:.c=.o}

INCD	=	includes/minishell.h

NAME	=	minishell

CFLAGS	=	-Wall -Wextra -Werror -lreadline

RM		=	rm -rf

CC		=	clang

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

all:			$(NAME)

$(NAME):	$(OBJ) $(INCD)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo ""
	@echo "|		minishell created		|"
	@echo ""

clean:
	$(RM) $(OBJ)
	@echo ""
	@echo "|		minishell deleted		|"
	@echo ""

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re git
