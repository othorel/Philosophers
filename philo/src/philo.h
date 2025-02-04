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

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define RESET   "\x1b[0m" 

# define MAX_PHILO 200

typedef struct s_data
{
	int				num_of_philos;
	int				num_of_forks;
	int				num_of_eat;
	int				stop;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long long int	time_start;
	pthread_t		check_monitor;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*mutex_fork;
}					t_data;

typedef struct s_philo
{
	int				index;
	int				num_eat_count;
	long long int	time_meal;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

int			ft_init_philos(t_philo **philo, int ac, char **av);

void		ft_print_message(t_philo *philo, char *str);
void		*ft_check_monitor(void *arg);
void		*philo_start_simul(void *arg);
void		ft_start_simul(t_philo *philo);

int			ft_atol_av(const char *str);
int			ft_strlen(char *str);
int			ft_print_error(char *str);
long long	ft_get_time(void);
void		ft_usleep(long long time, t_data *data);

#endif