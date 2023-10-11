NAME_PROJECT = philo

SRCS = src/aux_functions.c src/init.c src/main.c src/more_functions.c src/philo.c
OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME_PROJECT)

.PHONY: all clean fclean re

$(NAME_PROJECT): $(OBJS)
	@cc $(FLAGS) $(OBJS) -o $(NAME_PROJECT)
	@echo  "$(CYAN)Compiling files $(GREEN)[Success]$(RESET)"
	@echo  "$(CYAN)Build ($(NAME_PROJECT)): $(GREEN)[Success]$(RESET)"

%.o: %.c
	@cc -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "$(YELLOW)Cleaned object files $(RED)[Success]$(RESET)"

fclean: clean
	@rm -f $(NAME_PROJECT)
	@echo  "$(YELLOW)Cleaned $(CYAN)$(NAME_PROJECT): $(RED)[Success]$(RESET)"

re: fclean all

GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RED	= \033[1;31m
RESET = \033[0m
