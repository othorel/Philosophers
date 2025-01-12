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
	t_philo *table;

	table = setup_table(ac, av);
	if (!table)
		return (1);
	if (!start_simulation(table))
		return (1);
	cleanup_table(&table);
	return (0);
}
