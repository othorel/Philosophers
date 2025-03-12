/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:28:17 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/12 17:36:34 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_av(t_philo *philo, char **av)
{
	philo->num_of_philos = ft_atol_av(av[1]);
	philo->time_to_die = ft_atol_av(av[2]);
	philo->time_to_eat = ft_atol_av(av[3]);
	philo->time_to_sleep = ft_atol_av(av[4]);
	if (av[5])
		philo->num_times_to_eat = ft_atol_av(av[5]);
	else
		philo->num_times_to_eat = -1;
}

void	ft_init_philo(t_philo *philo, t_data *data, pthread_mutex_t *forks,
		char **av)
{
	int	i;

	i = 0;
	while (i < ft_atol_av(av[1]))
	{
		philo[i].id = i + 1;
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;	
		ft_init_av(&philo[i], av);
		philo[i].start_time = ft_get_time();
		philo[i].last_meal = ft_get_time();
		philo[i].write_lock = &data->write_lock;
		philo[i].dead_lock = &data->dead_lock;
		philo[i].meal_lock = &data->meal_lock;
		philo[i].dead = &data->flag;
		philo[i].left_fork = &forks[i];
		if (i == 0)
			philo[i].right_fork = &forks[philo[i].num_of_philos - 1];
		else
			philo[i].right_fork = &forks[i - 1];
		i++;
	}
}

void	ft_init_forks(pthread_mutex_t *forks, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}
