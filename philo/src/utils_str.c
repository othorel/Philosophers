/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:08:03 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/12 17:03:55 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_print_error(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(2, str, len);
	write(2, "\n", 1);
	exit (1);
}

int	ft_dead_lock(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	ft_print_message(char *str, t_philo *philo, int id)
{
	long long	time;

	pthread_mutex_lock(philo->write_lock);
	time = ft_get_time() - philo->start_time;
	if (!ft_dead_lock(philo))
		printf("%lld %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}
