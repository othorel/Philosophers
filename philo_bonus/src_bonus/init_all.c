/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:05:15 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/14 14:37:48 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*ft_init_data(int ac, char **av)
{
	t_philo	*temp;

	temp = (t_philo *)malloc(sizeof(t_philo));
	if (!temp)
		ft_print_error(RED "[Error: Failed to malloc philo]" RESET);
	temp->num_philos = ft_atol_av(av[1]);
	temp->num_forks = temp->num_philos;
	temp->time_to_die = ft_atol_av(av[2]);
	temp->time_to_eat = ft_atol_av(av[3]);
	temp->time_to_sleep = ft_atol_av(av[4]);
	if (temp->num_philos < 1 || temp->num_philos > 200
		|| temp->time_to_die == -1 || temp->time_to_eat == -1
		|| temp->time_to_sleep == -1)
		ft_print_error(RED "[Error: Wrong arguments]" RESET);
	temp->num_eat = -1;
	if (ac == 6)
	{
		temp->num_eat = ft_atol_av(av[5]);
		if (temp->num_eat == -1)
			ft_print_error(RED "[Error: Wrong arguments]" RESET);
	}
	temp->num_eat_count = 0;
	temp->stop = 0;
	temp->died = 0;
	return (temp);
}

t_philo	*ft_init_philo(int ac, char **av)
{
	t_philo	*temp;

	if (ac < 5 || ac > 6)
		ft_print_error(RED "[Error: Wrong number of arguments]" RESET);
	temp = ft_init_data(ac, av);
	temp->pid = (int *)malloc(sizeof(int) * temp->num_forks);
	if (!temp->pid)
		ft_print_error(RED "[Error: malloc error (init pid)]" RESET);
	sem_unlink("/write_lock");
	sem_unlink("/fork_lock");
	temp->write_lock = sem_open("/write_lock", O_CREAT, 0644, 1);
	temp->fork_lock = sem_open("/fork_lock", O_CREAT, \
								0644, temp->num_forks);
	if (temp->write_lock == NULL || temp->fork_lock == NULL)
		ft_print_error(RED "[Error: semaphore open error]" RESET);
	return (temp);
}
