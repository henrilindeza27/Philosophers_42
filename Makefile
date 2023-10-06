NAME = philo


SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME) $(BONUS)

.PHONY: all, fclean, re

$(NAME): $(OBJS)
		cc $(FLAGS) $(OBJS) -o $(NAME) 

clean:
	rm -f $(OBJS) 
	
fclean: clean
	rm -f $(NAME)

re: fclean all