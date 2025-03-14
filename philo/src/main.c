/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:41:03 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/12 16:53:01 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data			data;
	t_philo			philo[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];

	if (ac != 5 && ac != 6)
		return (ft_print_error(RED "[Wrong arguments count]" RESET), 1);
	if (ft_check_av(av) == 1)
		return (1);
	ft_init_mutex(&data, philo);
	ft_init_forks(forks, ft_atol_av(av[1]));
	ft_init_philo(philo, &data, forks, av);
	ft_create_thread(&data, forks);
	ft_destory_mutex(NULL, &data, forks);
	return (0);
}
