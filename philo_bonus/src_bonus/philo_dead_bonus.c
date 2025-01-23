/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dead_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:39:50 by olthorel          #+#    #+#             */
/*   Updated: 2025/01/23 11:43:41 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_dead(t_philo *philo, size_t die)
{
	sem_wait(philo->meal_lock);
	if (ft_get_time() - philo->last_meal >= (long)die && philo->eating == 0)
	{
		sem_post(philo->meal_lock);
		return (1);
	}
	sem_post(philo->meal_lock);
	return (0);
}

int	check_if_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].num_of_philos)
	{
		if (philo_dead(&philo[i], philo[i].time_to_die))
		{
			ft_print_message("Philo died", &philo[i], philo[i].id);
			sem_wait(philo[0].dead_lock);
			*philo->dead = 1;
			sem_post(philo[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_ate(t_philo *philo)
{
	int	i;
	int	eat;

	i = 0;
	eat = 0;
	if (philo[0].num_times_to_eat == -1)
		return (0);
	while (i < philo[0].num_of_philos)
	{
		sem_wait(philo[i].meal_lock);
		if (philo[i].meals_eaten >= philo[i].num_times_to_eat)
			eat++;
		sem_post(philo[i].meal_lock);
		i++;
	}
	if (eat == philo[0].num_of_philos)
	{
		sem_wait(philo[0].dead_lock);
		*philo->dead = 1;
		sem_post(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*sem_monitor(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (check_if_dead(philo) == 1 || check_if_ate(philo) == 1)
			break ;
	}
	return (ptr);
}
