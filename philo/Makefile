# Variables
SRCS        =   src/check_args.c     \
				src/init_all.c       \
				src/main.c           \
				src/philo_dead.c     \
				src/simulation.c     \
				src/thread.c         \
				src/utils.c                   

OBJ_DIR     =   obj
OBJS        =   $(SRCS:philo/%.c=$(OBJ_DIR)/%.o)

HEADERS     =   ./src/philo.h    

NAME        =   philo

CC          =   cc
CFLAGS      =   -Wall -Wextra -Werror -g -pthread

# Commandes colorées et décoratives
GREEN       =   \033[1;35m
CYAN        =   \033[1;34m
RESET       =   \033[0m
SMILEY      =   👍😎

# Règle pour générer chaque fichier .o dans obj/
$(OBJ_DIR)/%.o: src/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Cible principale
all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@echo "$(CYAN)Linking...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME) $(CFLAGS)
	@echo "$(GREEN)Executable $(NAME) created! $(SMILEY)$(RESET)"
	@echo "$(GREEN)Usage: ./philo [time_to_die] [time_to_eat] [time_to_sleep]$(RESET)"

# Nettoyage des fichiers objets
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(CYAN)Object files cleaned!$(RESET)"

# Nettoyage complet
fclean: clean
	@rm -rf $(NAME)
	@echo "$(CYAN)Executable $(NAME) removed!$(RESET)"

# Recompiler à partir de zéro
re: fclean all

# Éviter les conflits avec des fichiers portant les noms des cibles
.PHONY: all clean fclean re