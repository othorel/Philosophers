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

typedef struct s_philo
{
	int				id;
	int				nb_meals;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;

}					t_philo;

typedef struct s_table
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	int				dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	t_philo			*philos;
}					t_table;

void	print_action(t_philo *philo, char *action);
void	*philo_life(void *arg);
void	start_simulation(t_table *table);

int		init_table(t_table *table, int ac, char **av);

int		check_args(int ac, char **av);

t_table	*setup_table(int ac, char **av);
void	*clean_table(t_table **table);

int		ft_isnumeric(char *str);
int		ft_atoi(char *str);
void	ft_putstr_fd(char *str, int fd);
long	get_time(void);
void	sleep_ms(long time);

#endif