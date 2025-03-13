/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:33:42 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/13 16:38:51 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_philo	philo[MAX_PHILO];
	t_data	data;
	pid_t	pid[MAX_PHILO];
	int		i;

	(void)ac;
	ft_init_philo(philo, &data, av);
	philo->start_time = ft_get_time();
	i = -1;
	while (++i < philo[0].num_of_philos)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			ft_print_error(RED "Error fork" RESET);
		if (pid[i] == 0)
		{
			ft_routine(&philo[i]);
			exit(0);
		}
	}
	ft_destroy_sem(NULL, &data);
	return (0);
}
