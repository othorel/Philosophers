/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:03:11 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/14 10:29:11 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int ft_print_error(char *str, t_data *data, t_philo *philo, int malloc)
{
	sem_close(data->death);
	sem_unlink("/death");
	sem_close(data->fork);
	sem_unlink("/fork");
	if (malloc)
	{
		if (philo)
			free(philo);
	}
	printf("%s\n", str);
	return (1);
}

void	ft_print_message(t_philo *philo, char *str)
{
	sem_wait(philo->data->death);
	if (philo->data->over)
	{
		sem_post(philo->data->death);
		return ;
	}
	printf("%ld %d %s\n", ft_get_time() - philo->thread_start, philo->id, str);
	sem_post(philo->data->death);
}
