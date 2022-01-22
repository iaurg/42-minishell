# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/19 22:38:45 by itaureli          #+#    #+#              #
#    Updated: 2022/01/22 16:32:02 by itaureli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	src/minishell.c src/parse.c src/readline.c

OBJECTS		=	${SRC:.c=.o}

MINI_HEADER	=	includes/minishell.h

NAME	=	minishell

LBFT_DIR = ./libs/libft

LBFT_LIB = ${LBFT_DIR}/libft.a

CFLAGS	=	-Wall -Wextra -Werror -lreadline

RM		=	rm -rf

CC		=	clang

MSG1 = @echo "Compiled ✔︎"

MSG2 = @echo "Cleaned ✔︎"

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(LBFT_LIB) $(OBJECTS) $(MINI_HEADER)
	$(CC) $(CFLAGS) $(OBJECTS) $(LBFT_LIB) -o $(NAME)
	${MSG1}

${LBFT_LIB}:
	@${MAKE} -C ${LBFT_DIR}

clean:
	$(RM) $(OBJECTS)
	@${MAKE} fclean -C ${LBFT_DIR}
	${MSG2}

fclean: clean
	${RM} ${NAME} ${NAME_BONUS}
	@${MAKE} fclean -C ${LBFT_DIR}

run:
	${MAKE} && ./minishell.a
	${MSG1}

re:			fclean all

.PHONY:		all clean fclean re git
