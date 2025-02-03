/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:56:51 by olthorel          #+#    #+#             */
/*   Updated: 2025/02/03 13:29:30 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <semaphore.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <fcntl.h>
# include <signal.h>

# define MAX_PHILO 200

typedef struct s_philo
{
	int			id;
	int			eating;
	int			meals_eaten;
	int			num_of_philos;
	int			num_times_to_eat;
	int			*dead;
	long		last_meal;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long long	start_time;
	pid_t		pid;
	sem_t		*forks;
	sem_t		*write_lock;
	sem_t		*meal_lock;
	sem_t		*dead_lock;
}				t_philo;

typedef struct s_data
{
	int			dead_flag;
	sem_t		write_lock;
	sem_t		meal_lock;
	sem_t		dead_lock;
	t_philo		*philo;
}				t_data;

void	ft_putstr_fd(char *str, int fd);
void	ft_print_message(char *str, t_philo *philo, int id);
int		ft_isnumeric(char *av);
int		ft_check_args(char **av);

void	ft_init_input(t_philo *philo, char **av);
void	ft_init_forks(sem_t **forks, int philo);
void	ft_init_philos(t_philo *philo, t_data *data, sem_t *forks, char **av);
void	ft_init_data(t_data *data, t_philo *philo);

int		ft_dead_loop(t_philo *philo);
void	*ft_philo_simul(void *ptr);
int		ft_create_process(t_data *data, t_philo *philo);

void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_philo(t_philo *philo);
int		ft_atoll(char *str);
int		ft_strlen(char *str);
void	ft_sem_destroy(char *str, t_data *data);
int		ft_get_time(void);
int		ft_usleep(unsigned int ms);

int		philo_dead(t_philo *philo, size_t die);
int		check_if_dead(t_philo *philo);
int		check_if_ate(t_philo *philo);
void	*sem_monitor(void *ptr);

#endif