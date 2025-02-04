/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:52:16 by olthorel          #+#    #+#             */
/*   Updated: 2025/02/04 15:05:52 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
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

long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long long time, t_philo *philo)
{
	long long	i;

	i = ft_get_time();
	while (!philo->stop)
	{
		if (ft_get_time() - i >= time)
			break ;
		usleep(500);
	}
}

void	ft_print_message(t_philo *philo, char *str)
{
	sem_wait(philo->block_print);
	if (!philo->stop)
		printf("%lld %d %s\n", ft_get_time() - philo->time_start,
			philo->index, str);
	sem_post(philo->block_print);
}
