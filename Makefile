CC = cc

CFLAGS = -Werror -Wall -Wextra -g #-fsanitize=address

# FSANITIZER = -g -fsanitize=address

NAME = pipex

SRCS = pipex.c command_utils.c path_utils.c

OBJS = $(SRCS:.c=.o)

LIBFT =Libft.a
LIBRARY_DIR = Libft

all: $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIBRARY_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L $(LIBRARY_DIR) -lft

debug: $(CFLAGS) += $(FSANITIZER)
debug: $(NAME)

clean:
	rm -f $(OBJS)
	make -C $(LIBRARY_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBRARY_DIR) fclean

re: fclean all

t: $(NAME)
	 ./$(NAME)