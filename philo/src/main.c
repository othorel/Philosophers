/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:41:03 by olthorel          #+#    #+#             */
/*   Updated: 2025/02/03 09:44:54 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table			table;
	t_philo			philo[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];

	if (ac != 5 && ac != 6)
		return (ft_putstr_fd(RED "Wrong number of arguments\n" RESET, 2), 1);
	if (ft_check_args(av) == 1)
		return (1);
	ft_init_table(&table, philo);
	ft_init_forks(forks, ft_atoll(av[1]));
	ft_init_philos(philo, &table, forks, av);
	ft_create_thread(&table, forks);
	ft_mutex_destroy(NULL, &table, forks);
	return (0);
}
