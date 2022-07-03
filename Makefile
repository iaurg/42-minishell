# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/19 22:38:45 by itaureli          #+#    #+#              #
#    Updated: 2022/07/03 18:47:02 by itaureli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
#                                DEFINITION                                    #
# ---------------------------------------------------------------------------- #

# base settings
ARCHIVES_PATH = ./archives
INCLUDES_PATH = ./includes
NAME	=	minishell
OBJECTS_PATH = ./objects
SRC_PATH = ./src

# imports
EXTERNAL_LIBS = -lreadline
INTERNAL_LIBS = -lft -lgnl

# minishell
SRC		= code.c \
	execute.c \
	execute_system.c \
	expand.c \
	here_doc.c \
	minishell.c \
	pipe.c \
	pipe_execute.c \
	print_error.c \
	readline.c \
	redir.c \
	signal.c \
	tokens.c \
	utils.c \
	utils2.c \
	prohibited.c

SRC_MAIN = $(SRC)
SRC_MAIN += main.c # <- the program entrypoint
SRCS_NO_ENTRY = $(addprefix $(SRC_PATH)/,$(SRC))
SRCS = $(addprefix $(SRC_PATH)/,$(SRC_MAIN))
SRC_OBJECTS_PATH = $(OBJECTS_PATH)/$(NAME)
OBJECTS = $(addprefix $(SRC_OBJECTS_PATH)/,$(subst .c,.o,$(SRC_MAIN)))
MINI_HEADER	=	includes/minishell.h
LIBS_PATH = ./libs

# libft
LBFT_NAME = libft.a
LBFT_DIR = $(LIBS_PATH)/libft
LBFT_LIB = ${LBFT_DIR}/$(LBFT_NAME)
LBFT_ARCHIVE = $(ARCHIVES_PATH)/$(LBFT_NAME)

# Builtins
BUILTINS_NAME = libbuiltins.a
BUILTINS_SOURCES_FILES		= builtin_utils.c \
	builtin_utils2.c \
	builtins.c \
	builtins_cd.c \
	builtins_export.c \
	cd.c \
	dispatcher.c \
	echo.c \
	env.c \
	export.c \
	unset.c \
	utils3.c

BUILTINS_SOURCES_PATH = ./libs/builtins
BUILTINS_SOURCES = $(addprefix $(BUILTINS_SOURCES_PATH)/,$(BUILTINS_SOURCES_FILES))
BUILTINS_OBJECTS_PATH = $(OBJECTS_PATH)/builtins
BUILTINS_OBJECTS = $(addprefix $(BUILTINS_OBJECTS_PATH)/,$(subst .c,.o,$(BUILTINS_SOURCES_FILES)))
BUILTINS_HEADER_FILE = builtins.h
BUILTINS_HEADER = $(addprefix $(INCLUDES_PATH)/,$(BUILTINS_HEADER_FILE))
BUILTINS_ARCHIVE = $(ARCHIVES_PATH)/$(BUILTINS_NAME)

# libgnl
GNL = libgnl.a
GNL_PATH = $(LIBS_PATH)/get_next_line
GNL_ARCHIVE = $(ARCHIVES_PATH)/$(GNL)

# commands
CFLAGS	=	-Wall -Wextra -Werror
CC = gcc
RM		=	rm -rf
ARCHIVE = @ar -rc
SAFE_MKDIR = mkdir -p
MAKE_EXTERNAL = make -C
COPY = cp
MSG1 = @echo "Compiled ✔︎"
MSG2 = @echo "Cleaned ✔︎"
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q --tool=memcheck

# tests
TEST_NAME = test
TEST_FILES = minunit_example.c
TEST_PATH = ./tests
TESTS = $(addprefix $(TEST_PATH)/,$(TEST_FILES))

# ---------------------------------------------------------------------------- #
#                                COMPILATION                                   #
# ---------------------------------------------------------------------------- #
all: libft get_next_line $(NAME)

$(NAME): $(MINI_HEADER)
	$(CC) $(CFLAGS) -o $(NAME) -w $(SRCS) $(BUILTINS_SOURCES) -L $(ARCHIVES_PATH) -I $(INCLUDES_PATH) $(EXTERNAL_LIBS) $(INTERNAL_LIBS)

libft: $(LBFT_ARCHIVE)

$(LBFT_ARCHIVE): ${LBFT_LIB}
	@$(SAFE_MKDIR) $(ARCHIVES_PATH)
	@$(COPY) $(LBFT_DIR)/libft.a $(ARCHIVES_PATH)

${LBFT_LIB}:
	@$(MAKE_EXTERNAL) ${LBFT_DIR}

get_next_line: $(GNL_ARCHIVE)

$(GNL_ARCHIVE):
	@$(MAKE_EXTERNAL) $(GNL_PATH)
	@$(SAFE_MKDIR) $(ARCHIVES_PATH)
	@$(COPY) $(GNL_PATH)/$(GNL) $(ARCHIVES_PATH)

get_next_line_clean:
	$(MAKE_EXTERNAL) $(GNL_PATH) fclean
	$(REMOVE) $(GNL_ARCHIVE)

builtins: $(BUILTINS_ARCHIVE)

$(BUILTINS_ARCHIVE): $(BUILTINS_NAME)
	@cp ./$(BUILTINS_NAME) ./archives
	@rm $(BUILTINS_NAME)

$(BUILTINS_NAME): $(BUILTINS_OBJECTS)
	@$(ARCHIVE) $@ $^

$(BUILTINS_OBJECTS): $(BUILTINS_SOURCES) $(BUILTINS_HEADER)
	@$(SAFE_MKDIR) $(BUILTINS_OBJECTS_PATH)
	@$(CC) $(CFLAGS) -g -I $(INCLUDES_PATH) -o $@ -c $<

test:
	@$(CC) tests/test_unit.c \
	libs/libft/*.c libs/builtins/*.c libs/get_next_line/*.c \
	$(SRCS_NO_ENTRY) -I $(INCLUDES_PATH) \
	-lreadline -lrt -lm \
	-o test_unit && ./test_unit
	@$(RM) test_unit

test_builtins:
	python3 -m unittest tests.test_builtins -c

# https://github.com/CleanCut/green
test_builtins_color:
	green tests/test_builtins.py

clean:
	$(RM) $(OBJECTS)
	$(RM) $(BUILTINS_OBJECTS)
	@${MAKE} fclean -C ${LBFT_DIR}
	@${MAKE} fclean -C ${GNL_PATH}
	${RM} ${BUILTINS_OBJECTS_PATH}
	${MSG2}

fclean: clean
	${RM} ${NAME} ${NAME_BONUS}
	${RM} ${TEST_NAME}
	${RM} ${ARCHIVES_PATH}/${BUILTINS_NAME}
	${RM} ${ARCHIVES_PATH}/${LBFT_NAME}
	${RM} ${ARCHIVES_PATH}/${GNL}
	@${MAKE} fclean -C ${LBFT_DIR}

run:
	${MAKE} && ./minishell.a
	${MSG1}

valgrind:
	${MAKE} && ${VALGRIND} ./minishell
	${MSG1}

re:			fclean all

.PHONY:		all clean fclean re run git libft builtins get_next_line
