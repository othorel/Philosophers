/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:32:13 by olthorel          #+#    #+#             */
/*   Updated: 2025/01/12 16:32:13 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;
	int		i;

	i = 0;
	if (init_table(&table, ac, av))
	{
		printf("Error: invalid arguments\n");
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [must_eat_count]\n");
		return (1);
	}
	start_simulation(&table);
	while (i < table.nb_philo)
	{
		pthread_mutex_destroy(&table.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table.print_lock);
	free(table.forks);
	free(table.philos);
	return (0);
}
