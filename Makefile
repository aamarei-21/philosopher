NAME = philo

LIB = lib.a

SRC = main.c \
	check.c \
	init.c \
	utils/iseven.c \
	utils/err_func.c \
	utils/clean.c \
	utils/get_time.c \
	utils/ft_strlen.c \
	utils/ft_calloc.c \
	utils/ft_atoi.c \
	utils/ft_itoa.c \
	utils/ft_strcmp.c

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(LIB)
	$(CC) $(CFLAGS) $^ -o $(NAME)

$(LIB): $(OBJ)
	ar rcs $(LIB) $?

%.o: %.c
	$(CC) $(СFLAGS) -o $@ -c $< -I.

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME) $(LIB)

re: fclean all

dbg: $(SRC)
	$(CC) -g $(CFLAGS) $(SRC) -o dbg -I.