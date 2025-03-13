/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:56:51 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/13 16:48:16 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define RESET   "\x1b[0m"

# define MAX_PHILO 200

typedef struct s_philo
{
	int				id;
	int				eating;
	int				meals_eaten;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	long			last_meal;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	pthread_t		thread;
	sem_t			*forks;
	sem_t			*write_lock;
	sem_t			*dead_lock;
	sem_t			*meal_lock;
}					t_philo;

typedef struct s_data
{
	int				flag;
	sem_t			*dead_lock;
	sem_t			*meal_lock;
	sem_t			*write_lock;
	sem_t			*forks;
	t_philo			*philos;
}					t_data;

/* ************************************************************************** */
/*							INIT         									  */
/* ************************************************************************** */

void	ft_init_av(t_philo *philo, char **av);
void	ft_init_philo(t_philo *philo, t_data *data, char **av);
void	ft_init_forks(pthread_mutex_t *forks, int nb);

/* ************************************************************************** */
/*							MONITORING   									  */
/* ************************************************************************** */

int		ft_check(t_philo *philo, long long time_to_die);
int		ft_check_if_dead(t_philo *philo);
int		ft_check_meal(t_philo *philo);
void	*ft_monitoring(void *ptr);

/* ************************************************************************** */
/*							SIMULATION   									  */
/* ************************************************************************** */

void	ft_think(t_philo *philo);
void	ft_dream(t_philo *philo);
void	ft_eat(t_philo *philo);
void	*ft_routine(void *ptr);

/* ************************************************************************** */
/*							UTILS ARGV										  */
/* ************************************************************************** */

int		ft_is_numeric(char *av);
int		ft_atol_av(const char *str);
int		ft_check_av(char **av);

/* ************************************************************************** */
/*							UTILS MUTEX										  */
/* ************************************************************************** */

void	ft_init_mutex(t_data *data, t_philo *philo);
void	ft_destroy_sem(char *str, t_data *data);
int		ft_create_sem(t_data *data);

/* ************************************************************************** */
/*							UTILS STR										  */
/* ************************************************************************** */

int		ft_strlen(char *str);
int		ft_print_error(char *str);
int		ft_dead_lock(t_philo *philo);
void	ft_print_message(char *str, t_philo *philo, int id);

/* ************************************************************************** */
/*							UTILS TIME										  */
/* ************************************************************************** */

int		ft_get_time(void);
int		ft_usleep(long long ms);

#endif