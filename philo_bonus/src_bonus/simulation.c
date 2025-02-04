/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:42:22 by olthorel          #+#    #+#             */
/*   Updated: 2025/02/04 13:45:11 by olthorel         ###   ########.fr       */
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
				philo->index, RED "died 💀" RESET);
			sem_post(philo->block_print);
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
	if (philo->num_of_philos == 1)
	{
		ft_print_message(philo, GREEN "has taken a fork 🍴 but can't eat ..." RESET);
		ft_usleep(philo->time_to_die, philo);
		ft_print_message(philo, RED "died 💀" RESET);
		exit (1);
	}
	if (philo->index % 2 == 1)
		usleep(500);
	while (1)
	{
		sem_wait(philo->block_fork);
		ft_print_message(philo, GREEN "has taken a fork 🍴" RESET);
		sem_wait(philo->block_fork);
		ft_print_message(philo, GREEN "has taken a fork 🍴" RESET);
		ft_print_message(philo, YELLOW "is eating 🍝" RESET);
		sem_post(philo->block_fork);
		sem_post(philo->block_fork);
		ft_usleep(philo->time_to_eat, philo);
		philo->time_meal = ft_get_time();
		philo->num_eat_count += 1;
		ft_print_message(philo, BLUE "is sleeping 😴" RESET);
		ft_usleep(philo->time_to_sleep, philo);
		ft_print_message(philo, MAGENTA "is thinking 🤔" RESET);
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
			while (++i < temp->num_of_philos)
				kill(temp->pid[i], SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(temp->block_print);
	sem_close(temp->block_fork);
	sem_close(temp->block_meal);
	sem_unlink("/block_print");
	sem_unlink("/block_fork");
	sem_unlink("/block_meal");
	ft_free_philo(temp);
}
