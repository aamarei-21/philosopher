NAME = philo

SRC = philo.c\
	ft_thread_phil.c\
	ft_utils.c\
	ft_subsidary.c\

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) :
	$(CC) $(CFLAGS) $^ -o $(NAME)


%.o: %.c
	$(CC) $(СFLAGS) -o $@ -c $< -I.

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

dbg: $(SRC)
	$(CC) -g $(CFLAGS) $(SRC) -o dbg -I.
