/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:05:15 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/14 10:44:31 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_init_philo(t_data *data, t_philo *philo)
{
	int	i;
	
	i = 0;
	while (i < data->num)
	{
		philo[i].id = i + 1;
		philo[i].dead = 0;
		philo[i].iter_num = 0;
		philo[i].thread_start = 0;
		philo[i].last_meal = 0;
		philo[i].data = data;
		i++;
	}
	return (0);
}

int	ft_init_sem(t_data *data)
{
	sem_unlink("/death");
	sem_unlink("/fork");
	data->death = sem_open("/death", O_CREAT, 0666, 1);
	if (data->death == SEM_FAILED)
		return (ft_print_error("Error: sem_open\n", data, 0, 1));
	data->fork = sem_open("/fork", O_CREAT, 0666, data->num);
	if (data->fork == SEM_FAILED)
		return (ft_print_error("Error: sem_open\n", data, 0, 1));
	return (0);
}

int	ft_init_data(t_data *data, char **av)
{
	int	sem;
	
	sem = -1;
	data->num = ft_atol_av(av[1]);
	data->time_to_die = ft_atol_av(av[2]);
	data->time_to_eat = ft_atol_av(av[3]);
	data->time_to_sleep = ft_atol_av(av[4]);
	data->max_iter = -2;
	data->check_meal = 0;
	data->ready = 0;
	if (av[5])
	{
		data->check_meal = 1;
		data->max_iter = ft_atol_av(av[5]);
	}
	data->over = 0;
	if (data->num > 0)
	sem = ft_init_sem(data);
	return (sem || data->num <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
			|| data->max_iter == 0 || data->max_iter == -1);
}
