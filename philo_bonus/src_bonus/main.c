/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:33:42 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/14 11:11:50 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;
	
	memset(&data, 0, sizeof(t_data));
	if ((ac != 5 && ac != 6) || ft_init_data(&data, av))
		return (ft_print_error("Error: invalid arguments\n", &data, 0, 1));
	if (ft_philosophers(&data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
