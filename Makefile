# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/19 22:38:45 by itaureli          #+#    #+#              #
#    Updated: 2022/04/20 21:13:55 by vwildner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	minishell.c readline.c wip_lexer.c print_error.c

SRC_PATH = ./src

SRCS = $(addprefix $(SRC_PATH)/,$(SRC))

OBJECTS		=	${SRCS:.c=.o}

MINI_HEADER	=	includes/minishell.h

NAME	=	minishell

LBFT_DIR = ./libs/libft

LBFT_LIB = ${LBFT_DIR}/libft.a

CFLAGS	=	-Wall -Wextra -lreadline -g -O0

RM		=	rm -rf

CC := $(shell ./set_compiler.sh)

MSG1 = @echo "Compiled ✔︎"

MSG2 = @echo "Cleaned ✔︎"

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q --tool=memcheck

# Minunit Tests
TEST_NAME = test

TEST_FILES = minunit_example.c

TEST_PATH = ./tests

TESTS = $(addprefix $(TEST_PATH)/,$(TEST_FILES))

# Builtins library

BUILTINS_NAME = builtins.a

BUILTINS_SOURCES_FILES		= builtins.c cmd_echo.c dispatcher.c env.c export.c

BUILTINS_SOURCES_PATH = ./libs/builtins

BUILTINS_SOURCES = $(addprefix $(BUILTINS_SOURCES_PATH)/,$(BUILTINS_SOURCES_FILES))

BUILTINS_OBJECTS_PATH = ./objects/builtins

BUILTINS_OBJECTS = $(addprefix $(BUILTINS_OBJECTS_PATH)/,$(subst .c,.o,$(BUILTINS_SOURCES_FILES)))

BUILTINS_HEADER_FILE = builtins.h

EXTERNAL_LIBS = -lreadline

INCLUDES_PATH = ./includes

BUILTINS_HEADER = $(addprefix $(INCLUDES_PATH)/,$(BUILTINS_HEADER_FILE))

ARCHIVE = @ar -rc

SAFE_MKDIR = mkdir -p

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(LBFT_LIB) $(OBJECTS) $(MINI_HEADER)
	$(CC) $(CFLAGS) $(OBJECTS) $(LBFT_LIB) -o $(NAME)
	${MSG1}

libft: $(LBFT_LIB)

${LBFT_LIB}:
	@${MAKE} -C ${LBFT_DIR}

builtins: $(BUILTINS_NAME)
	@cp ./$(BUILTINS_NAME) ./archives
	@rm $(BUILTINS_NAME)

$(BUILTINS_NAME): $(BUILTINS_OBJECTS)
	$(ARCHIVE) $@ $^

$(BUILTINS_OBJECTS_PATH)/%.o: $(BUILTINS_SOURCES_PATH)/%.c $(BUILTINS_HEADER)
	@$(SAFE_MKDIR) $(BUILTINS_OBJECTS_PATH)
	@$(CC) $(CFLAGS) -g -I $(INCLUDES_PATH) -L ./archives/libft.a -o $@ -c $< $(EXTERNAL_LIBS)

test: $(NAME)
	$(CC) $(TESTS) -lrt -lm -o $(TEST_NAME)
	./$(TEST_NAME)

test_builtins:
	python3 -m unittest tests.test_builtins -c

clean:
	$(RM) $(OBJECTS)
	@${MAKE} fclean -C ${LBFT_DIR}
	${RM} ${BUILTINS_OBJECTS_PATH}
	${MSG2}

fclean: clean
	${RM} ${NAME} ${NAME_BONUS}
	${RM} ${TEST_NAME}
	${RM} ${BUILTINS_NAME}.a
	@${MAKE} fclean -C ${LBFT_DIR}

run:
	${MAKE} && ./minishell.a
	${MSG1}

re:			fclean all

.PHONY:		all clean fclean re git
