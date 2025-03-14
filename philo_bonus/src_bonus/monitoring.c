/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:03:30 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/14 11:18:49 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_check_meals(t_philo philo, int last_meal)
{
	if (philo.data->check_meal && last_meal == philo.data->num -1
		&& philo.iter_num == philo.data->max_iter)
		return (ft_usleep(300));
	return (0);
}

void	*ft_check_thread(void *ptr)
{
	int		i;
	t_philo	*philo;
	t_data	*data;
	
	data = (t_data *)ptr;
	philo = (t_philo *)data->philo;
	while (!data->ready)
		continue;
	while (!data->over)
	{
		i = -1;
		while (++i < data->num)
		{
			if (ft_check_death(&philo[i]) || ft_check_meals(philo[i], i))
				data->over = 1;
		}
	}
	return (NULL);
}

int	ft_init_thread(t_data *data, t_philo *philo)
{
	pthread_t	death;
	int			i;

	i = -1;
	data->start = ft_get_time();
	if (pthread_create(&death, NULL, &ft_check_thread, data) == -1)
		return (ft_print_error("Error\nFailed to create death thread\n", data, philo, 2));
	while (++i < data->num)
	{
		philo[i].thread_start = data->start;
		philo[i].last_meal = data->start;
		if (pthread_create(&philo[i].thread, NULL,
				&ft_routine, &philo[i]) == -1)
			return (ft_print_error("Error\nFailed to create thread\n", data, philo, 2));
	}
	data->ready = 1;
	pthread_join(death, NULL);
	return (0);
}

void	ft_end_thread(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->num)
		pthread_join(philo[i].thread, NULL);
	ft_usleep(2 * data->num);
	sem_close(data->death);
	sem_unlink("/death");
	sem_close(data->fork);
	sem_unlink("/fork");
	free(philo);
}

int	ft_philosophers(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->num);
	if (!data->philo || ft_init_philo(data, data->philo))
		return (EXIT_FAILURE);
	if (ft_init_thread(data, data->philo))
		return (EXIT_FAILURE);
	ft_end_thread(data, data->philo);
	return (0);
}
