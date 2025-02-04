/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:51:55 by olthorel          #+#    #+#             */
/*   Updated: 2025/02/04 17:20:03 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	if (!philo->data->stop)
		printf("%lld %d %s\n", ft_get_time() - philo->data->time_start,
			philo->index, str);
	pthread_mutex_unlock(&philo->data->mutex_print);
}

void	*ft_check_monitor(void *arg)
{
	t_philo	*philo;
	int		i;
	int		flag;

	philo = (t_philo *)arg;
	while (!philo->data->stop)
	{
		i = -1;
		flag = 0;
		while (++i < philo->data->num_of_philos)
		{
			if (ft_get_time() - (philo + i)->time_meal > philo->data->time_to_die)
			{
				ft_print_message(philo, RED "died 💀" RESET);
				philo->data->stop = 1;
				break ;
			}
			if (philo->data->num_of_eat != -1 && (philo + i)->num_eat_count >= philo->data->num_of_eat)
				flag++;
		}
		if (flag == philo->data->num_of_philos)
			philo->data->stop = 1;
	}
	return (NULL);
}

void	*philo_start_simul(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->stop)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print_message(philo, GREEN "has taken a fork 🍴" RESET);
		pthread_mutex_lock(philo->right_fork);
		ft_print_message(philo, GREEN "has taken a fork 🍴" RESET);
		ft_print_message(philo, YELLOW "is eating 🍝" RESET);
		ft_usleep(philo->data->time_to_eat, philo->data);
		philo->time_meal = ft_get_time();
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (!philo->data->stop)
			philo->num_eat_count += 1;
		ft_print_message(philo, BLUE "is sleeping 😴" RESET);
		ft_usleep(philo->data->time_to_sleep, philo->data);
		ft_print_message(philo, MAGENTA "is thinking 🤔" RESET);
	}
	return (NULL);
}

void	ft_start_simul(t_philo *philo)
{
	int	i;

	i = -1;
	philo->data->time_start = ft_get_time();
	while (++i < philo->data->num_of_philos)
	{
		(philo + i)->time_meal = ft_get_time();
		if (pthread_create(&(philo + i)->thread, NULL, &philo_start_simul, philo + i))
			ft_print_error(RED "Error creation thread" RESET);
		pthread_detach((philo + i)->thread);
		usleep(500);
	}
	if (pthread_create(&philo->data->check_monitor, NULL, &ft_check_monitor, philo))
		ft_print_error(RED "Error creation thread" RESET);
	if (pthread_join(philo->data->check_monitor, NULL))
		ft_print_error(RED "Error join thread" RESET);
	i = -1;
	while (++i < philo->data->num_of_forks)
		pthread_mutex_destroy(&philo->data->mutex_fork[i]);
	pthread_mutex_destroy(&philo->data->mutex_print);
}
