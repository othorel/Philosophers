/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:03:11 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/14 14:34:52 by olthorel         ###   ########.fr       */
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

void	ft_print_message(t_philo *philo, char *str)
{
	sem_wait(philo->write_lock);
	if (!philo->stop)
		printf("%lld %d %s\n", ft_get_time() - philo->time_to_start,
			philo->index, str);
	sem_post(philo->write_lock);
}
