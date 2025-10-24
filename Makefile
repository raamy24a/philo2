NAME = philo 

SRC_FILES = main.c threads.c philo_helper.c philo.c more_philo.c main_help.c
OBJ = $(SRC_FILES:.c=.o)

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
