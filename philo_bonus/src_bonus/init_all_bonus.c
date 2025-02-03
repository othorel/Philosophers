/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:24:42 by olthorel          #+#    #+#             */
/*   Updated: 2025/02/03 13:26:28 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_init_input(t_philo *philo, char **av)
{
	philo->num_of_philos = ft_atoll(av[1]);
	philo->time_to_die = ft_atoll(av[2]);
	philo->time_to_eat = ft_atoll(av[3]);
	philo->time_to_sleep = ft_atoll(av[4]);
	if (av[5])
		philo->time_to_eat = ft_atoll(av[5]);
	else
		philo->time_to_eat = -1;
}

void	ft_init_forks(sem_t **forks, int philo)
{
	int	i;

	i = 0;
	while (i < philo)
	{
		sem_unlink("/fork");
		forks[i] = sem_open("/fork", O_CREAT, 0644, 1);
		i++;
	}
}

void	ft_init_philos(t_philo *philo, t_data *data, sem_t *forks,
			char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoll(av[1]))
	{
		philo[i].id = i + 1;
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;
		ft_init_input(&philo[i], av);
		philo[i].start_time = ft_get_time();
		philo[i].last_meal = ft_get_time();
		philo[i].write_lock = &data->write_lock;
		philo[i].dead_lock = &data->dead_lock;
		philo[i].meal_lock = &data->meal_lock;
		philo[i].dead = &data->dead_flag;
		philo[i].forks = forks;
		i++;
	}
}

void	ft_init_data(t_data *data, t_philo *philo)
{
	data->dead_flag = 0;
	data->philo = philo;
	sem_unlink("/write_lock");
	data->write_lock = sem_open("/write_lock", O_CREAT, 0644, 1);
	sem_unlink("/meal_lock");
	data->meal_lock = sem_open("/meal_lock", O_CREAT, 0644, 1);
	sem_unlink("/dead_lock");
	data->dead_lock = sem_open("/dead_lock", O_CREAT, 0644, 1);
}
