/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:11:48 by olthorel          #+#    #+#             */
/*   Updated: 2025/01/23 16:48:35 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_table			table;
	t_philo			philo[MAX_PHILO];
	sem_t			*forks;

	if (ac != 5 && ac != 6)
		return (ft_putstr_fd("Wrong number of arguments", 2), 1);
	if (ft_check_args(av) == 1)
		return (1);
	ft_init_table(&table, philo);
	forks = ft_create_sem(&table, ft_atoll(av[1]));
	ft_init_philos(philo, &table, forks, av);
	ft_sem_destroy(NULL, &table, forks);
	return (0);
}