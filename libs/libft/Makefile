NAME = libft.a
SOURCES = ft_isalpha.c ft_isdigit.c ft_isalnum.c

# Add more files to sources
SOURCES += ft_isascii.c ft_isprint.c ft_strlen.c
SOURCES += ft_tolower.c ft_toupper.c
SOURCES += ft_memset.c ft_bzero.c ft_memcpy.c
SOURCES += ft_memmove.c ft_strlcpy.c ft_strlcat.c
SOURCES += ft_strchr.c ft_strrchr.c ft_strncmp.c
SOURCES += ft_memchr.c ft_memcmp.c ft_strnstr.c
SOURCES += ft_atoi.c ft_calloc.c ft_strdup.c
SOURCES += ft_substr.c ft_strjoin.c ft_strtrim.c
SOURCES += ft_split.c ft_putchar_fd.c ft_putstr_fd.c
SOURCES += ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c
SOURCES += ft_striteri.c ft_itoa.c
SOURCES += ft_getenv.c ft_strtok.c
SOURCES += ft_lstpush.c ft_lstunshift.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
SOURCES += ft_free.c ft_lstlast.c

# Use same files from sources, but change .c to .o
OBJECTS = ${SOURCES:.c=.o}

# @ supress commands to show in terminal
RM = @rm -f

MSG1 = @echo "Compiled ✔︎"
MSG2 = @echo "Cleaned ✔︎"

# Adds object files *.o static library libft.a, creating libft.a if it no exist.
ARCHIVE = @ar -rc

# Create an index for the library
#RANLIB = @ranlib

# Compile files following above rules 	${CC} -o ${NAME} ${OBJECTS}
$(NAME): ${OBJECTS}
	@${ARCHIVE} ${NAME} ${OBJECTS} ${NAME}
	@${MSG1}

# Default all command to compile
all: ${NAME}

# Clean generated .o files
clean:
	@${RM} ${OBJECTS} ${BONUS_OBJECTS}
	@${MSG2}

# Force clean all files generated on all
fclean: clean
	@${RM} ${NAME}

# Regenarate compilation
re: fclean all

# phony will run, independent from the state of the file system, avoid make in files with same name
.PHONY: all clean fclean re
