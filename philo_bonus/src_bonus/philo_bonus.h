/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:56:51 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/14 11:18:55 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <semaphore.h>

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define RESET   "\x1b[0m"

# define LEFT_FORK 0
# define RIGHT_FORK 1

typedef struct s_data
{
	int				num;
	int				ready;
	int				max_iter;
	int				check_meal;
	int				over;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start;
	void			*philo;
	sem_t			*death;
	sem_t			*fork;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				dead;
	int				iter_num;
	long			thread_start;
	long			last_meal;
	pthread_t		thread;
	t_data			*data;
}					t_philo;

/* ************************************************************************** */
/*							INIT         									  */
/* ************************************************************************** */

int	ft_init_philo(t_data *data, t_philo *philo);
int	ft_init_sem(t_data *data);
int	ft_init_data(t_data *data, char **av);

/* ************************************************************************** */
/*							MONITORING   									  */
/* ************************************************************************** */

int	ft_check_meals(t_philo philo, int last_meal);
void	*ft_check_thread(void *ptr);
int	ft_init_thread(t_data *data, t_philo *philo);
void	ft_end_thread(t_data *data, t_philo *philo);
int	ft_philosophers(t_data *data);

/* ************************************************************************** */
/*							SIMULATION   									  */
/* ************************************************************************** */

int	ft_died(t_philo *philo, int unlock, int print);
int	ft_check_death(t_philo *philo);
void	ft_sleep_and_think(t_philo *philo);
void	ft_eat(t_philo *philo);
void	*ft_routine(void *ptr);

/* ************************************************************************** */
/*							UTILS ARGV										  */
/* ************************************************************************** */

int		ft_is_numeric(char *av);
int		ft_atol_av(const char *str);

/* ************************************************************************** */
/*							UTILS STR										  */
/* ************************************************************************** */

int ft_print_error(char *str, t_data *data, t_philo *philo, int malloc);
void	ft_print_message(t_philo *philo, char *str);

/* ************************************************************************** */
/*							UTILS TIME										  */
/* ************************************************************************** */

int		ft_get_time(void);
int		ft_usleep(long long ms);

#endif