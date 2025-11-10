NAME = philosophers
CC = cc
# -Wall -Wextra -Werror 
CFLAGS = -MMD -g
SRC = philosophers.c ft_philosophers_helpers.c ft_actions.c stopwatch.c thread_functions.c
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean: 
	rm -f $(OBJ) $(DEP)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re
