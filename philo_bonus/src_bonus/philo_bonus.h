/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:56:51 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/14 14:33:39 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define RESET   "\x1b[0m"

typedef struct s_philo
{
	int				num_philos;
	int				num_forks;
	int				num_eat;
	int				num_eat_count;
	int				stop;
	int				died;
	int				*pid;
	int				index;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long long int	time_to_start;
	long long int	time_to_meal;
	sem_t			*write_lock;
	sem_t			*fork_lock;
	pthread_t		check_monitor;
}					t_philo;

/* ************************************************************************** */
/*							INIT         									  */
/* ************************************************************************** */

t_philo		*ft_init_data(int ac, char **av);
t_philo		*ft_init_philo(int ac, char **av);

/* ************************************************************************** */
/*							MONITORING   									  */
/* ************************************************************************** */

void		*ft_check_monitoring(void *av);
void		ft_exit_philo(t_philo **philo);

/* ************************************************************************** */
/*							SIMULATION   									  */
/* ************************************************************************** */

void		ft_routine(t_philo *philo);

/* ************************************************************************** */
/*							UTILS ARGV										  */
/* ************************************************************************** */

int			ft_is_numeric(char *av);
int			ft_atol_av(const char *str);

/* ************************************************************************** */
/*							UTILS STR										  */
/* ************************************************************************** */

int			ft_strlen(char *str);
int			ft_print_error(char *str);
void		ft_print_message(t_philo *philo, char *str);

/* ************************************************************************** */
/*							UTILS TIME										  */
/* ************************************************************************** */

long long	ft_get_time(void);
void		ft_usleep(long long ms, t_philo *philo);

#endif