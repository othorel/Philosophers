# Variables
SRCS        =  	src/init_all.c       \
				src/main.c           \
				src/monitoring.c     \
				src/simulation.c     \
				src/utils_av.c       \
				src/utils_mutex.c    \
				src/utils_str.c      \
				src/utils_time.c     

OBJ_DIR     =   obj
OBJS        =   $(SRCS:philo/%.c=$(OBJ_DIR)/%.o)

HEADERS     =   ./src/philo.h    

NAME        =   philo

CC          =   cc
CFLAGS      =   -Wall -Wextra -Werror -g -pthread

GREEN       =   \033[1;35m
CYAN        =   \033[1;34m
RESET       =   \033[0m
SMILEY      =   👍😎

$(OBJ_DIR)/%.o: src/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@echo "$(CYAN)Linking...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME) $(CFLAGS)
	@echo "$(GREEN)Executable $(NAME) created! $(SMILEY)$(RESET)"
	@echo "$(GREEN)Usage: ./philo [time_to_die] [time_to_eat] [time_to_sleep]$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(CYAN)Object files cleaned!$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(CYAN)Executable $(NAME) removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
