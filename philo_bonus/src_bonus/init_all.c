/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:05:15 by olthorel          #+#    #+#             */
/*   Updated: 2025/02/03 17:22:58 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_atoll(const char *str)
{
	unsigned long long	result;
	int					sign;
	int					i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

static t_philo	*ft_init_data(int ac, char **av)
{
	t_philo	*temp;

	temp = (t_philo *)malloc(sizeof(t_philo));
	if (!temp)
		return (ft_print_error(RED "Malloc error (philo)" RESET), NULL);
	temp->num_of_philos = ft_atoll(av[1]);
	temp->num_of_forks = temp->num_of_philos;
	temp->time_to_die = ft_atoll(av[2]);
	temp->time_to_eat = ft_atoll(av[3]);
	temp->time_to_sleep = ft_atoll(av[4]);
	if (temp->num_of_philos < 1 || temp->num_of_philos > MAX_PHILO
		|| temp->time_to_die == -1 || temp->time_to_eat == -1
		|| temp->time_to_sleep == -1)
		ft_print_error(RED "Invalid arguments" RESET);
	temp->num_of_eat = -1;
	if (ac == 6)
	{
		temp->num_of_eat = ft_atoll(av[5]);
		if (temp->num_of_eat == -1)
			ft_print_error(RED "Invalid arguments" RESET);
	}
	temp->num_eat_count = 0;
	temp->stop = 0;
	temp->died = 0;
	return (temp);
}

t_philo	*ft_init_philo(int ac, char **av)
{
	t_philo	*temp;

	if (ac < 5 || ac > 6)
		ft_print_error(RED "Invalid number of arguments" RESET);
	temp = ft_init_data(ac, av);
	temp->pid = (int *)malloc(sizeof(int) * temp->num_of_forks);
	if (!temp->pid)
		return (ft_print_error(RED "Malloc error (init pid)" RESET), NULL);
	sem_unlink("/block_print");
	sem_unlink("/block_fork");
	temp->block_print = sem_open("/block_print", O_CREAT, 0644, 1);
	temp->block_fork = sem_open("/block_fork", O_CREAT, 0644,
			temp->num_of_forks);
	if (temp->block_print <= 0 || temp->block_fork <= 0)
		ft_print_error(RED "Sem open error" RESET);
	return (temp);
}
