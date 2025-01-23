/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:13:34 by olthorel          #+#    #+#             */
/*   Updated: 2025/01/23 11:31:46 by olthorel         ###   ########.fr       */
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
		philo->num_times_to_eat = ft_atoll(av[5]);
	else
		philo->num_times_to_eat = -1;
}

void	ft_init_forks(sem_t *forks, int philo)
{
	int	i;

	i = 0;
	while (i < philo)
	{
		sem_init(&forks[i], 0, 1);
		i++;
	}
}

void	ft_init_philos(t_philo *philo, t_table *table, sem_t *forks, char **av)
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
		philo[i].write_lock = &table->write_lock;
		philo[i].dead_lock = &table->dead_lock;
		philo[i].meal_lock = &table->meal_lock;
		philo[i].dead = &table->dead_flag;
		philo[i].left_fork = &forks[i];
		if (i == 0)
			philo[i].right_fork = &forks[philo[i].num_of_philos - 1];
		else
			philo[i].right_fork = &forks[i - 1];
		i++;
	}
}

void	ft_init_table(t_table *table, t_philo *philo)
{
	table->dead_flag = 0;
	table->philos = philo;
	sem_init(&table->write_lock, 0, 1);
	sem_init(&table->dead_lock, 0, 1);
	sem_init(&table->meal_lock, 0, 1);
}
