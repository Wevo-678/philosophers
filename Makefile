
NAME = philo
DIR_SRC = src/
DIR_OBJ = obj/
CC = gcc
CFLAGS = -Wall -Wextra -Werror -ggdb
RM = rm -f

SRCS =  $(wildcard $(DIR_SRC)*.c) \


OBJS = $(SRCS:$(DIR_SRC)%.c=$(DIR_OBJ)%.o)

all: $(NAME)
	@clear

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(DIR_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all