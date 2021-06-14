NAME = libft.a

CC = gcc

CFLAGS =  -c -g -Wall -Werror -Wextra

LIB_FLAGS = -rcs

SRC0 = $(wildcard libft/*.c)

DST0 = $(SRC0:.c=.o)

all : $(NAME)

$(NAME) : $(DST0)
	ar $(LIB_FLAGS) $@ $^

libft/%.o : libft/%.c libft/libft.h
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(DST0) $(DST1)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
