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

# define RED "\001\033[1;31m\002"
# define GREEN "\001\033[1;32m\002"
# define YELLOW "\001\033[1;33m\002"
# define BLUE "\001\033[1;34m\002"
# define PURPLE "\001\033[1;35m\002"
# define CYAN "\001\033[1;36m\002"
# define WHITE "\001\033[0;37m\002"
# define BOLD_WHITE "\001\033[1;37m\002"

typedef struct s_philo
{
	int				id;
	int				nb_meals;
	long			last_meal;
	int				is_done;
	int				*is_over;
	t_table			table;
	pthread_mutex_t	thread_id;
	pthread_mutex_t	last_meal_lock;
	pthread_mutex_t	is_done_lock;
	pthread_mutex_t	*print_zone;
	pthread_mutex_t	*forks[2];
	pthread_mutex_t	*is_over_lock;

}					t_philo;

typedef struct s_table
{
	long			start_time;
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_meals;
	int				is_over;
	t_philo			**philos;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	pthread_mutex_t	is_over_lock;
	phread_t		reaper;
}					t_table;

enum e_fork{
	RIGHT,
	LEFT
};

t_table	*setup_table(int ac, char **av);

int		create_philo(int i, t_table *table);

int		ft_isum(char *str);
int		ft_atoi(char *str);
long	get_time(void);