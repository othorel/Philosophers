/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:47:01 by olthorel          #+#    #+#             */
/*   Updated: 2025/01/23 16:59:51 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_dead_loop(t_philo *philo)
{
	sem_wait(philo->dead_lock);
	if (*philo->dead == 1)
		return (sem_post(philo->dead_lock), 1);
	sem_post(philo->dead_lock);
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

int	ft_start_simulation(t_table *table, sem_t *forks)
{
	pid_t	pid;
	int			i;

	pid = fork();
    if (pid == 0)
    {
        thread_monitor(table->philos);
        exit (0);
    }
    i = 0;
	while (i < table->philos[0].num_of_philos)
	{
		pid = fork();
		if (pid == 0)
		{
			ft_philo_simul(&table->philos[i]);
			exit (0);
		}
		i++;
	}
	i = 0;
	while (i < table->philos[0].num_of_philos + 1)
	{
		wait(NULL);
		i++;
	}
	return (0);
}

