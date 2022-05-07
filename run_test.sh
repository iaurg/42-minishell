#!/usr/bin/sh
# WARNING: This testing script only works for the minishell module.
# If you want to test builtins try running `make test_builtins`
# Usage: ./run_test.sh <test_name>

cc tests/test_$1.c \
  libs/libft/*.c libs/builtins/*.c src/wip_lexer.c src/readline.c src/print_error.c src/signal.c src/execute.c\
  -lreadline -lrt -lm \
  -o test_$1 \
    && ./test_$1 \
	&& rm ./test_$1
