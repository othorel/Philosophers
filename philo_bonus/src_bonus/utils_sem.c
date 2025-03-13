/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:03:19 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/13 16:50:44 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_init_sem(t_data *data, t_philo *philo)
{
	data->flag = 0;
	data->philos = philo;
	sem_unlink("write_lock");
	sem_unlink("dead_lock");
	sem_unlink("meal_lock");
	sem_unlink("forks");
	data->write_lock = sem_open("write_lock", O_CREAT, 0644, 1);
	data->dead_lock = sem_open("dead_lock", O_CREAT, 0644, 1);
	data->meal_lock = sem_open("meal_lock", O_CREAT, 0644, 1);
	data->forks = sem_open("forks", O_CREAT, 0644, data->philos[0].num_of_philos);
	if (data->write_lock == SEM_FAILED || data->dead_lock == SEM_FAILED ||
        data->meal_lock == SEM_FAILED || data->forks == SEM_FAILED)
    {
        ft_print_error(RED "Error initializing semaphores" RESET);
        exit(EXIT_FAILURE);
    }
}

void	ft_destroy_sem(char *str, t_data *data)
{
	int	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	sem_close(data->write_lock);
	sem_close(data->dead_lock);
	sem_close(data->meal_lock);
	sem_close(data->forks);
	sem_unlink("write_lock");
	sem_unlink("dead_lock");
	sem_unlink("meal_lock");
	sem_unlink("forks");
}

int	ft_create_sem(t_data *data)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &ft_monitoring, data->philos) != 0)
		ft_destroy_sem(RED "[Thread creation error]" RESET, data);
	i = 0;
	while (i < data->philos[0].num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &ft_routine,
				&data->philos[i]) != 0)
			ft_destroy_sem(RED "[Thread creation error]" RESET, data);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		ft_destroy_sem(RED "[Thread join error]" RESET, data);
	while (i < data->philos[0].num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			ft_destroy_sem(RED "[Thread join error]" RESET, data);
		i++;
	}
	return (0);
}
