/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:51:55 by olthorel          #+#    #+#             */
/*   Updated: 2025/02/03 15:57:36 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_print_message(GREEN "Has taken a fork 🍴" RESET, philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	ft_print_message(GREEN "Has taken a fork 🍴" RESET, philo, philo->id);
	philo->eating = 1;
	ft_print_message(YELLOW "Is eating 🍝" RESET, philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = ft_get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_message(BLUE "Is sleeping 😴" RESET, philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	ft_philo(t_philo *philo)
{
	ft_print_message(MAGENTA "Is thinking 🤔" RESET, philo, philo->id);
}
