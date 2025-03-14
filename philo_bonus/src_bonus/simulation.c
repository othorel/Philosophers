/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:42:22 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/14 14:27:55 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_routine(t_philo *philo)
{
	if (pthread_create(&philo->check_monitor, \
			NULL, &ft_check_monitoring, philo))
		ft_print_error(RED "[Error: Failed to create the thread]" RESET);
	if (philo->index % 2 == 0)
		usleep(1000);
	while (1)
	{
		sem_wait(philo->fork_lock);
		ft_print_message(philo, GREEN "has taken a fork" RESET);
		sem_wait(philo->fork_lock);
		ft_print_message(philo, GREEN "has taken a fork" RESET);
		ft_print_message(philo, YELLOW "is eating" RESET);
		ft_usleep(philo->time_to_eat, philo);
		philo->time_to_meal = ft_get_time();
		sem_post(philo->fork_lock);
		sem_post(philo->fork_lock);
		philo->num_eat_count += 1;
		ft_print_message(philo, BLUE "is sleeping" RESET);
		ft_usleep(philo->time_to_sleep, philo);
		ft_print_message(philo, MAGENTA "is thinking" RESET);
	}
	if (pthread_join(philo->check_monitor, NULL))
		ft_print_error(RED "[Error: Failed to join the thread]" RESET);
}
