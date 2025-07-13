CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = philo
SRCS = ft_atoi.c monitoring.c philo.c routine.c parsing_threads.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -lpthread -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

