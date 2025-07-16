CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -pthread
NAME    = philo
SRCS    = ft_atoi.c monitoring.c philo.c routine.c parsing_threads.c utils.c
OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
