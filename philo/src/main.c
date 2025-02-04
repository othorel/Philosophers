/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:41:03 by olthorel          #+#    #+#             */
/*   Updated: 2025/02/04 17:14:22 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac < 5 || ac > 6)
		return (ft_print_error(RED "Error number of arguments" RESET));
	if (ft_init_philos(&philo, ac, av) == -1)
		return (ft_print_error(RED "Error init philos" RESET), 0);
	ft_start_simul(philo);
	return (0);
}

