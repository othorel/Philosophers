/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:03:30 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/13 15:01:49 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_check(t_philo *philo, long long time_to_die)
{
	sem_wait(philo->meal_lock);
	if (ft_get_time() - philo->last_meal >= time_to_die)
		return (sem_post(philo->meal_lock), 1);
	sem_post(philo->meal_lock);
	return (0);
}

int	ft_check_if_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].num_of_philos)
	{
		if (ft_check(&philo[i], philo[i].time_to_die))
		{
			ft_print_message(RED "died" RESET, &philo[i], philo[i].id);
			sem_wait(philo[0].dead_lock);
			*philo->dead = 1;
			sem_post(philo[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_meal(t_philo *philo)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philo[0].num_times_to_eat == -1)
		return (0);
	while (i < philo[0].num_of_philos)
	{
		sem_wait(philo[i].meal_lock);
		if (philo[i].meals_eaten >= philo[i].num_times_to_eat)
			finished_eating++;
		sem_post(philo[i].meal_lock);
		i++;
	}
	if (finished_eating == philo[0].num_of_philos)
	{
		sem_wait(philo[0].dead_lock);
		*philo->dead = 1;
		sem_post(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*ft_monitoring(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (ft_check_if_dead(philo) == 1 || ft_check_meal(philo) == 1)
			break ;
	}
	return (ptr);
}
