/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:38:24 by olthorel          #+#    #+#             */
/*   Updated: 2025/02/03 11:46:55 by olthorel         ###   ########.fr       */
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

int	ft_create_process(t_data *data, t_philo *philo)
{
	pid_t	pid;
	int			i;

	i = 0;
	while (i < philo[0].num_of_philos)
	{
		pid = fork();
		if (pid == -1)
		{
			ft_sem_destroy("Error: fork failed", data, NULL);
			return (1);
		}
		if (pid == 0)
		{
			philo[i].pid = getpid();
			ft_philo_simul(&philo[i]);
			exit(0);
		}
		i++;
	}
	while (i < philo[0].num_of_philos)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	return (0);
}