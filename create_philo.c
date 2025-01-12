/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:10:30 by olthorel          #+#    #+#             */
/*   Updated: 2025/01/12 17:10:30 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void set_args(t_philo *philo, t_table *table)
{
	philo->start_time = table->start_time;
	philo->nb_philo = table->nb_philo;
	philo->time_to_die = table->time_to_die;
	philo->time_to_eat = table->time_to_eat;
	philo->time_to_sleep = table->time_to_sleep;
	philo->nb_meals = table->nb_meals;
}

static void set_ptrs(int i, t_philo *philo, t_table *table)
{
	philo->print_zone = &table->print;
	philo->forks[LEFT] = &table->forks[i];
	philo->forks[RIGHT] = &table->forks[(i + 1) % table->nb_philo];
	philo->is_over = &table->is_over;
	philo->is_over_lock = &table->is_over_lock;
}

static void set_fts(t_philo *philo)
{
	philo->ft[0] = eat;
	philo->ft[1] = sleep;
	philo->ft[2] = think;
}

int	create_philo(int i, t_table *table)
{
	table->philos[i] = malloc(sizeof(t_philo));
	if (!table->philos[i])
		return (0);
	table->philos[i]->id = i + 1;
	table->philos[i]->thread_id = 0;
	table->philos[i]->nb_meals = 0;
	table->philos[i]->is_done = 0;
	pthread_mutex_init(&table->philos[i]->is_done_lock, NULL);
	set_args(table->philos[i], table);
	set_ptrs(i, table->philos[i], table);
	set_fts(table->philos[i]);
	table->philos[i]->last_meal = get_time();
	pthread_mutex_init(&table->philos[i]->last_meal_lock, NULL);
	print_log(table->philos[i], "Started simulation", BOLD_WHITE);
	return (1);
}
