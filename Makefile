# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/19 22:38:45 by itaureli          #+#    #+#              #
#    Updated: 2022/06/01 22:36:21 by vwildner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= minishell.c readline.c wip_lexer.c print_error.c execute.c utils.c execute_system.c redir.c utils2.c signal.c prompt.c here_doc.c expand.c tokens.c parse_whitespace.c parse_whitespace_utils.c pipe.c pipe_execute.c

SRC_MAIN = $(SRC)
SRC_MAIN += main.c

SRC_PATH = ./src

SRCS_NO_ENTRY = $(addprefix $(SRC_PATH)/,$(SRC))

SRCS = $(addprefix $(SRC_PATH)/,$(SRC_MAIN))

OBJECTS		=	${SRCS:.c=.o}

MINI_HEADER	=	includes/minishell.h

NAME	=	minishell

LBFT_DIR = ./libs/libft

LBFT_LIB = ${LBFT_DIR}/libft.a

CFLAGS	=	-Wall -Wextra -g -O0 -Og

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

BUILTINS_NAME = libbuiltins.a

BUILTINS_SOURCES_FILES		= builtins.c echo.c dispatcher.c env.c export.c builtins_export.c builtin_utils.c builtins_cd.c builtin_utils2.c

BUILTINS_SOURCES_PATH = ./libs/builtins

BUILTINS_SOURCES = $(addprefix $(BUILTINS_SOURCES_PATH)/,$(BUILTINS_SOURCES_FILES))

BUILTINS_OBJECTS_PATH = ./objects/builtins

BUILTINS_OBJECTS = $(addprefix $(BUILTINS_OBJECTS_PATH)/,$(subst .c,.o,$(BUILTINS_SOURCES_FILES)))

BUILTINS_HEADER_FILE = builtins.h

EXTERNAL_LIBS = -lreadline
INTERNAL_LIBS = -lbuiltins -lft -lgnl

INCLUDES_PATH = ./includes

BUILTINS_HEADER = $(addprefix $(INCLUDES_PATH)/,$(BUILTINS_HEADER_FILE))

ARCHIVES_PATH = ./archives
ARCHIVE = @ar -rc

SAFE_MKDIR = mkdir -p

# libgnl
MAKE_EXTERNAL = make -C
LIBFT_PATH = $(LIBS_PATH)/libft
GNL = libgnl.a
GNL_PATH = $(LIBS_PATH)/get_next_line
GNL_ARCHIVE = $(ARCHIVES_PATH)/$(GNL)

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(LBFT_LIB) $(OBJECTS) $(MINI_HEADER)
	gcc -g -Wall -Wextra -o minishell ./src/*.c ./libs/builtins/*.c ./libs/libft/*.c ./libs/get_next_line/*.c -C -lreadline

libft: $(LBFT_LIB)

${LBFT_LIB}:
	@${MAKE} -C ${LBFT_DIR}

builtins: $(BUILTINS_NAME)
	@cp ./$(BUILTINS_NAME) ./archives
	@rm $(BUILTINS_NAME)

build_get_next_line:
	@$(MAKE_EXTERNAL) $(GNL_PATH)
	@$(SAFE_MKDIR) $(ARCHIVES_PATH)
	@$(COPY) $(GNL_PATH)/$(GNL) $(ARCHIVES_PATH)

get_next_line_clean:
	$(MAKE_EXTERNAL) $(GNL_PATH) fclean
	$(REMOVE) $(GNL_ARCHIVE)

$(BUILTINS_NAME): $(BUILTINS_OBJECTS)
	$(ARCHIVE) $@ $^

$(BUILTINS_OBJECTS_PATH)/%.o: $(BUILTINS_SOURCES_PATH)/%.c $(BUILTINS_HEADER)
	@$(SAFE_MKDIR) $(BUILTINS_OBJECTS_PATH)
	@$(CC) $(CFLAGS) -g -I $(INCLUDES_PATH) -L ./archives/libft.a -o $@ -c $< $(EXTERNAL_LIBS)

test:
	@$(CC) tests/test_unit.c \
	libs/libft/*.c libs/builtins/*.c libs/get_next_line/*.c \
	$(SRCS_NO_ENTRY) \
	-lreadline -lrt -lm \
	-o test_unit && ./test_unit

test_builtins:
	python3 -m unittest tests.test_builtins -c

# https://github.com/CleanCut/green
test_builtins_color:
	green tests/test_builtins.py

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

valgrind:
	${MAKE} && ${VALGRIND} ./minishell
	${MSG1}

re:			fclean all

.PHONY:		all clean fclean re git
