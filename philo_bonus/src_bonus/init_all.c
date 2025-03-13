/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:05:15 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/13 16:49:16 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	ft_init_philo(t_philo *philo, t_data *data, char **av)
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
		philo[i].write_lock = data->write_lock;
		philo[i].dead_lock = data->dead_lock;
		philo[i].meal_lock = data->meal_lock;
		philo[i].dead = &data->flag;
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
