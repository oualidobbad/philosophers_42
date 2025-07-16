CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -pthread
OBJFOLDER  = obj
NAME    = philo
SRCS    = ft_atoi.c monitoring.c philo.c routine.c parsing_threads.c utils.c
OBJS    = $(SRCS:%.c=$(OBJFOLDER)/%.o)

all: $(OBJFOLDER) $(NAME)

$(OBJFOLDER):
	@mkdir -p $(OBJFOLDER)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJFOLDER)/%.o: %.c 
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJFOLDER)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
