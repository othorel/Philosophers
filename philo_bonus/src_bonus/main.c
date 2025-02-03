/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:10:15 by olthorel          #+#    #+#             */
/*   Updated: 2025/02/03 11:33:04 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		philo[MAX_PHILO];
	sem_t		forks[MAX_PHILO];

	if (ac != 5 && ac != 6)
		return (ft_putstr_fd(RED "Wrong number of arguments\n" RESET, 2), 1);
	if (ft_check_args(av) == 1)
		return (1);
	ft_init_data(&data, philo);
	ft_init_forks(forks, ft_atoll(av[1]));
	ft_init_philos(philo, &data, forks, av);
	ft_create_sem(&data, forks);
	ft_sem_destroy(NULL, &data, forks);
	return (0);
}