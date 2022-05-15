NAME = libgnl.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
FILES = get_next_line_utils.c\
		get_next_line.c
OBJECTS = $(FILES:.c=.o)

RE = rm -f

all: $(NAME)

$(NAME): $(OBJECTS)
	@ar -rcs $(NAME) $(OBJECTS)

$(OBJECTS): $(FILES)
	@$(CC) $(FLAGS) -c $(FILES)

clean:
	@$(RM) $(OBJECTS) $(BONUS_OBJECTS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
