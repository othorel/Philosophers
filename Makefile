NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = create_philo.c utils.c main.c setup_table.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all