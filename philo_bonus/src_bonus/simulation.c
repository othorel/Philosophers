/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:42:22 by olthorel          #+#    #+#             */
/*   Updated: 2025/02/03 17:24:48 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_check_monitor(void *ac)
{
	t_philo	*philo;

	philo = (t_philo *)ac;
	while (!philo->stop)
	{
		usleep(500);
		if (ft_get_time() - philo->time_meal > philo->time_to_die)
		{
			philo->died = 1;
			sem_wait(philo->block_print);
			printf("%lld %d %s\n", ft_get_time() - philo->time_start,
				philo->index, RED "Philo died 💀" RESET);
			philo->stop = 1;
			break ;
		}
		if (philo->num_of_eat != -1 && philo->num_eat_count
			>= philo->num_of_eat)
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

void	philo_start_simul(t_philo *philo)
{
	if (pthread_create(&philo->check_monitor, NULL, &ft_check_monitor, philo))
		ft_print_error(RED "Error create thread" RESET);
	if (philo->index % 2 == 1)
		usleep(500);
	while (1)
	{
		sem_wait(philo->block_fork);
		sem_wait(philo->block_fork);
		ft_print_message(philo, GREEN "Has taken a fork 🍴" RESET);
		ft_print_message(philo, GREEN "Has taken a fork 🍴" RESET);
		ft_print_message(philo, YELLOW "Is eating 🍝" RESET);
		ft_usleep(philo->time_to_eat, philo);
		philo->time_meal = ft_get_time();
		sem_post(philo->block_fork);
		sem_post(philo->block_fork);
		philo->num_eat_count += 1;
		ft_print_message(philo, BLUE "Is sleeping 😴" RESET);
		ft_usleep(philo->time_to_sleep, philo);
		ft_print_message(philo, MAGENTA "Is thinking 🤔" RESET);
	}
	if (pthread_join(philo->check_monitor, NULL))
		ft_print_error(RED "Thread join failed" RESET);
}

void	ft_cleanup(t_philo **philo)
{
	t_philo	*temp;
	int		i;
	int		status;

	temp = *philo;
	i = 0;
	while (i < temp->num_of_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (i < temp->num_of_philos)
			{
				kill(temp->pid[i], SIGKILL);
				i++;
			}
			break ;
		}
		i++;
	}
	sem_close(temp->block_print);
	sem_close(temp->block_fork);
	sem_unlink("/block_print");
	sem_unlink("/block_fork");
}
