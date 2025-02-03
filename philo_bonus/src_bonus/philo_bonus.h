/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:56:51 by olthorel          #+#    #+#             */
/*   Updated: 2025/02/03 17:21:00 by olthorel         ###   ########.fr       */
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
	int				num_of_philos;
	int				num_of_forks;
	int				num_of_eat;
	int				num_eat_count;
	int				stop;
	int				died;
	int				*pid;
	int				index;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long long int	time_start;
	long long int	time_meal;
	sem_t			*block_print;
	sem_t			*block_fork;
	pthread_t		check_monitor;
}					t_philo;

t_philo		*ft_init_philo(int ac, char **av);
void		*ft_check_monitor(void *ac);
void		philo_start_simul(t_philo *philo);
void		ft_cleanup(t_philo **philo);

int			ft_strlen(char *str);
int			ft_print_error(char *str);
long long	ft_get_time(void);
void		ft_usleep(long long time, t_philo *philo);
void		ft_print_message(t_philo *philo, char *str);

#endif