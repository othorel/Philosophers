/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:57:16 by olthorel          #+#    #+#             */
/*   Updated: 2025/01/11 18:57:16 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define MAX_PHILO 300

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
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_table
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_table;

void	ft_putstr_fd(char *str, int fd);
void	ft_print_message(char *str, t_philo *philo, int id);
int		ft_isnumeric(char *av);
int		ft_atoll(char *str);
int		ft_strlen(char *str);
void	ft_mutex_destroy(char *str, t_table *table, pthread_mutex_t *forks);
int		ft_get_time(void);
int		ft_usleep(unsigned int ms);

int		ft_check_args(char **av);

void	ft_init_input(t_philo *philo, char **av);
void	ft_init_forks(pthread_mutex_t *forks, int philo);
void	ft_init_philos(t_philo *philo, t_table *table, pthread_mutex_t *forks,
			char **av);
void	ft_init_table(t_table *table, t_philo *philo);

int		philo_dead(t_philo *philo, size_t die);
int		check_if_dead(t_philo *philo);
int		check_if_ate(t_philo *philo);
void	*thread_monitor(void *ptr);

void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_philo(t_philo *philo);

int		ft_dead_loop(t_philo *philo);
void	*ft_philo_simul(void *ptr);
int		ft_create_thread(t_table *table, pthread_mutex_t *forks);

#endif