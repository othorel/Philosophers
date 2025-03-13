/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:03:11 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/13 14:25:54 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_wait(philo->dead_lock);
	if (*philo->dead == 1)
		return (sem_post(philo->dead_lock), 1);
	sem_post(philo->dead_lock);
	return (0);
}

void	ft_print_message(char *str, t_philo *philo, int id)
{
	long long	time;

	sem_wait(philo->write_lock);
	time = ft_get_time() - philo->start_time;
	if (!ft_dead_lock(philo))
		printf("%lld %d %s\n", time, id, str);
	sem_post(philo->write_lock);
}
