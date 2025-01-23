/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:44:55 by olthorel          #+#    #+#             */
/*   Updated: 2025/01/23 11:46:19 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_eat(t_philo *philo)
{
	sem_wait(philo->right_fork);
	ft_print_message("Has taken a fork", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		sem_post(philo->right_fork);
		return ;
	}
	sem_wait(philo->left_fork);
	ft_print_message("Has taken a fork", philo, philo->id);
	philo->eating = 1;
	ft_print_message("Is eating", philo, philo->id);
	sem_wait(philo->meal_lock);
	philo->last_meal = ft_get_time();
	philo->meals_eaten++;
	sem_post(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	sem_post(philo->left_fork);
	sem_post(philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_message("Is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	ft_philo(t_philo *philo)
{
	ft_print_message("Is thinking", philo, philo->id);
}
