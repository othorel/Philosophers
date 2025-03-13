SRCS        =  	src_bonus/init_all.c       \
				src_bonus/main.c           \
				src_bonus/monitoring.c     \
				src_bonus/simulation.c     \
				src_bonus/utils_av.c       \
				src_bonus/utils_sem.c      \
				src_bonus/utils_str.c      \
				src_bonus/utils_time.c                 

OBJ_DIR     =   obj
OBJS        =   $(SRCS:src_bonus/%.c=$(OBJ_DIR)/%.o)

HEADERS     =   ./src_bonus/philo_bonus.h    

NAME        =   philo_bonus

CC          =   cc
CFLAGS      =   -Wall -Wextra -Werror -g -pthread

GREEN       =   \033[1;35m
CYAN        =   \033[1;34m
RESET       =   \033[0m
SMILEY      =   👍😎

$(OBJ_DIR)/%.o: src_bonus/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@echo "$(CYAN)Linking...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME) $(CFLAGS)
	@echo "$(GREEN)Executable $(NAME) created! $(SMILEY)$(RESET)"
	@echo "$(GREEN)Usage: ./philo_bonus [time_to_die] [time_to_eat] [time_to_sleep]$(RESET)"

bonus: $(NAME)
	@echo "$(GREEN)Compilation bonus ok !$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(CYAN)Object files cleaned!$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(CYAN)Executable $(NAME) removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus

