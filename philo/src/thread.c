/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:50:33 by olthorel          #+#    #+#             */
/*   Updated: 2025/02/03 11:47:11 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*ft_philo_simul(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!ft_dead_loop(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_philo(philo);
	}
	return (ptr);
}

int	ft_create_thread(t_table *table, pthread_mutex_t *forks)
{
	pthread_t	create;
	int			i;

	if (pthread_create(&create, NULL, &thread_monitor, table->philos) != 0)
		ft_mutex_destroy("Thread creation erorr", table, forks);
	i = 0;
	while (i < table->philos[0].num_of_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &ft_philo_simul
				, &table->philos[i]) != 0)
			ft_mutex_destroy("Thread creation error", table, forks);
		i++;
	}
	i = 0;
	if (pthread_join(create, NULL) != 0)
		ft_mutex_destroy("Thread join error", table, forks);
	while (i < table->philos[0].num_of_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			ft_mutex_destroy("Thread join error", table, forks);
		i++;
	}
	return (0);
}
