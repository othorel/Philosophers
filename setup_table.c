/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:45:37 by olthorel          #+#    #+#             */
/*   Updated: 2025/01/12 16:45:37 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_args(int ac, char **av, t_table *table)
{
	table->philos->last_meal = get_time();
	table->nb_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->must_eat_count = ft_atoi(av[5]);
	else
		table->must_eat_count = -1;
	return (1);
}

static int	get_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->forks)
		return (0);
	while (i < table->nb_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	return (1);
}

static int	get_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philos)
		return (0);
	while (i < table->nb_philo)
	{
		if (!create_philo(i, table))
			return (0);
	}
	return (1);
}

t_table	*setup_table(int ac, char **av)
{
	t_table	*table;

	if (!check_args(ac, av))
		return (NULL);
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	pthread_mutex_init(&table->print_lock, NULL);
	pthread_mutex_init(&table->dead, NULL);
	if (!get_args(ac, av, table) || !get_forks(table) || !get_philos(table))
		return (clean_table(&table));
	table->dead = 0;
	if (table->nb_philo == 1)
		table->dead = 1;
	return (table);
}
