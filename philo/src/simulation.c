/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:51:55 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/13 10:11:49 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_thinking(t_philo *philo)
{
	ft_print_message(MAGENTA "is thinking" RESET, philo, philo->id);
}

void	ft_sleeping(t_philo *philo)
{
	ft_print_message(BLUE "is sleeping" RESET, philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_print_message(YELLOW "has taken a fork" RESET, philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	ft_print_message(YELLOW "has taken a fork" RESET, philo, philo->id);
	philo->eating = 1;
	ft_print_message(GREEN "is eating" RESET, philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = ft_get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*ft_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(50);
	while (!ft_dead_lock(philo))
	{
		ft_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
	}
	return (ptr);
}
