/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:46:40 by olthorel          #+#    #+#             */
/*   Updated: 2025/01/19 15:46:40 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
}

static void	destroy_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->philos[i].left_fork);
		pthread_mutex_destroy(&table->philos[i].right_fork);
		i++;
	}
	free(table->philos);
}

void	*clean_table(t_table **table)
{
	if (*table)
	{
		pthread_mutex_destroy(&(*table)->print_lock);
		pthread_mutex_destroy(&(*table)->dead);
		if ((*table)->forks)
			destroy_forks(*table);
		if ((*table)->philos)
			destroy_philos(*table);
		free(*table);
	}
	return (NULL);
}
