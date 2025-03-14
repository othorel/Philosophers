/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:42:22 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/14 11:23:28 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_died(t_philo *philo, int unlock, int print)
{
	if (unlock)
	{
		sem_post(philo->data->fork);
		sem_post(philo->data->fork);
	}
	if (print)
	{
		sem_wait(philo->data->death);
		printf("%ld %d %s\n", ft_get_time() - philo->thread_start,
			philo->id, "died");
		sem_post(philo->data->death);
	}
	return (1);
}

int	ft_check_death(t_philo *philo)
{
	long	now;

	sem_wait(philo->data->death);
	now = ft_get_time() - philo->last_meal;
	if (now >= philo->data->time_to_die)
	{
		philo->data->over = 1;
		philo->dead = 1;
		sem_post(philo->data->death);
		return (ft_died(philo, 1, 1));
	}
	sem_post(philo->data->death);
	return (0);
}

void	ft_sleep_and_think(t_philo *philo)
{
	ft_usleep(philo->data->time_to_sleep);
	ft_print_message(philo, "is sleeping");
	ft_print_message(philo, "is thinking");
}

void	ft_eat(t_philo *philo)
{
	sem_wait(philo->data->fork);
	ft_print_message(philo, "has taken a fork");
	sem_wait(philo->data->fork);
	ft_print_message(philo, "has taken a fork");
	philo->last_meal = ft_get_time();
	ft_print_message(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	philo->iter_num++;
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
}

void	*ft_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (!philo->data->ready)
		continue ;
	if (philo->id & 1)
		ft_usleep(philo->data->time_to_eat * 0.9 + 1);
	while (!philo->data->over)
	{
		ft_eat(philo);
		ft_sleep_and_think(philo);
	}
	return (NULL);
}
