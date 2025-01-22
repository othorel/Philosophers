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
NAME_BONUS  =   philo_bonus

CC          =   cc
CFLAGS      =   -Wall -Wextra -Werror -g -pthread

# Commandes colorées et décoratives
GREEN       =   \033[1;35m
CYAN        =   \033[1;34m
RESET       =   \033[0m
SMILEY      =   👍
SMILEY2	    =   😎

# Règle pour générer chaque fichier .o dans obj/
$(OBJ_DIR)/%.o: src/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Cible principale
all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@echo "$(CYAN)Linking...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME) $(CFLAGS)
	@echo "$(GREEN)Executable $(NAME) created! $(SMILEY2)$(RESET)"
	@echo "$(GREEN)Usage: ./philo$(RESET)"

# Cible bonus
bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS) $(HEADERS)
	@echo "$(CYAN)Linking bonus...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME_BONUS) $(CFLAGS)
	@echo "$(GREEN)Executable $(NAME_BONUS) created! $(SMILEY2)$(RESET)"
	@echo "$(GREEN)Usage: ./philo_bonus$(RESET)"

# Nettoyage des fichiers objets
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(CYAN)Object files cleaned!$(RESET)"

# Nettoyage complet
fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS)
	@echo "$(CYAN)Executable $(NAME) and $(NAME_BONUS) removed!$(RESET)"

# Recompiler à partir de zéro
re: fclean all

# Éviter les conflits avec des fichiers portant les noms des cibles
.PHONY: all clean fclean re bonus
