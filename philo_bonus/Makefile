NAME = philo_bonus

SRC = philo_bonus.c\
	ft_thread_phil.c\
	ft_utils.c\
	ft_subsidiary.c

SRCH = philo.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME)


%.o: %.c
	$(CC) $(СFLAGS) -o $@ -c $< -I.

norm:
	norminette $(SRC) $(SRCH)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

dbg: $(SRC)
	$(CC) -g $(CFLAGS) $(SRC) -o dbg -I.
