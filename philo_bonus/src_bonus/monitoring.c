/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:03:30 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/14 14:36:24 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_check_monitoring(void *av)
{
	t_philo	*philo;

	philo = (t_philo *)av;
	while (!philo->stop)
	{
		usleep(100);
		if (ft_get_time() - philo->time_to_meal > philo->time_to_die)
		{
			philo->died = 1;
			sem_wait(philo->write_lock);
			printf("%lld %d %s\n", ft_get_time() - philo->time_to_start,
				philo->index, RED "died" RESET);
			philo->stop = 1;
			break ;
		}
		if (philo->num_eat != -1 && philo->num_eat_count >= philo->num_eat)
		{
			philo->stop = 1;
			break ;
		}
	}
	if (philo->died)
		exit (1);
	else
		exit (0);
}

void	ft_exit_philo(t_philo **philo)
{
	t_philo	*temp;
	int		i;
	int		status;

	temp = *philo;
	i = 0;
	while (i < temp->num_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < temp->num_philos)
				kill(temp->pid[i], SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(temp->write_lock);
	sem_close(temp->fork_lock);
	sem_unlink("/write_lock");
	sem_unlink("/fork_lock");
	free(temp->pid);
	free(temp);
}
