/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:33:42 by olthorel          #+#    #+#             */
/*   Updated: 2025/02/03 16:52:46 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_philo	*philo;
	int		i;

	philo = ft_init_philo(ac, av);
	i = -1;
	philo->time_start = ft_get_time();
	while (++i < philo->num_of_philos)
	{
		philo->pid[i] = fork();
		if (philo->pid[i] == -1)
		{
			ft_print_error(RED "Error fork" RESET);
		}
		if (philo->pid[i] == 0)
		{
			philo->index = i + 1;
			philo->time_meal = ft_get_time();
			philo_start_simul(philo);
		}
	}
	ft_cleanup(&philo);
	return (0);
}
