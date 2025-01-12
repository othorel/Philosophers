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
	table->table.start_time = get_time();
	table->table.nb_philo = ft_atoi(av[1]);
	table->table.time_to_die = ft_atoi(av[2]);
	table->table.time_to_eat = ft_atoi(av[3]);
	table->table.time_to_sleep = ft_atoi(av[4]);
	table->table.nb_meals = -1;
	if (ac == 6)
		table->table.nb_meals = ft_atoi(av[5]);
	return (1);
}

static int	get_forks(t_table *table)
{
	int	i;

	i = -1;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->forks)
		return (0);
	while (++i < table->nb_philo)
		pthread_mutex_init(&table->forks[i], NULL);
	return (1);
}

static int	get_philos(t_table *table)
{
	int	i;

	i = -1;
	table->philos = malloc(sizeof(t_philo *) * table->nb_philo);
	if (!table->philos)
		return (0);
	while (++i < table->nb_philo)
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
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->is_over_lock, NULL);
	if (!get_args(ac, av, table) || !get_forks(table) || !get_philos(table))
		return (cleanup_table(&table));
	table->is_over = 0;
	if (table->nb_philo == 1)
		table->is_over = 1;
	return (table);
}
