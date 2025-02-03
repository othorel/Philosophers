/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:15:43 by olthorel          #+#    #+#             */
/*   Updated: 2025/02/03 13:15:03 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

void	ft_print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	sem_wait(philo->write_lock);
	time = ft_get_time() - philo->start_time;
	if (!ft_dead_loop(philo))
		printf("%zu %d %s\n", time, id, str);
	sem_post(philo->write_lock);
}

int	ft_isnumeric(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] < 48 || av[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_args(char **av)
{
	if (ft_atoll(av[1]) > MAX_PHILO || ft_atoll(av[1]) <= 0
		|| ft_isnumeric(av[1]) == 1)
		return (ft_putstr_fd("Invalid philos number\n", 2), 1);
	if (ft_atoll(av[2]) <= 0 || ft_isnumeric(av[2]) == 1)
		return (ft_putstr_fd("Invalid time to die\n", 2), 1);
	if (ft_atoll(av[3]) <= 0 || ft_isnumeric(av[3]) == 1)
		return (ft_putstr_fd("Invalid time to eat\n", 2), 1);
	if (ft_atoll(av[4]) <= 0 || ft_isnumeric(av[4]) == 1)
		return (ft_putstr_fd("Invalid time to sleep\n", 2), 1);
	if (av[5] && (ft_atoll(av[5]) < 0 || ft_isnumeric(av[5]) == 1))
		return (ft_putstr_fd("Invalid number of time each philos must eat\n"
				, 2), 1);
	return (0);
}
