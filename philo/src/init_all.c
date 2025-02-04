/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:28:17 by olthorel          #+#    #+#             */
/*   Updated: 2025/02/04 17:15:55 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atol_av(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = (result * 10) + (str[i] - 48);
		if (result > 2147483647)
			return (-1);
		i++;
	}
	if (str[i] != '\0' || result == 0)
		return (-1);
	return ((int)result);
}

static int	ft_init_data(t_data **data, int ac, char **av)
{
	t_data	*temp;

	temp = (t_data *)malloc(sizeof(t_data));
	if (!temp)
		return (ft_print_error(RED "Malloc error (data)" RESET), -1);
	temp->num_of_philos = ft_atol_av(av[1]);
	temp->num_of_forks = temp->num_of_philos;
	temp->time_to_die = ft_atol_av(av[2]);
	temp->time_to_eat = ft_atol_av(av[3]);
	temp->time_to_sleep = ft_atol_av(av[5]);
	if (temp->num_of_philos < 1 || temp->num_of_philos > MAX_PHILO
		|| temp->time_to_die == -1 || temp->time_to_eat == -1
		|| temp->time_to_sleep == -1)
		return (ft_print_error(RED "Error arguments" RESET), -1);
	temp->num_of_eat = -1;
	if (ac == 6)
	{
		temp->num_of_eat = ft_atol_av(av[5]);
		if (temp->num_of_eat == -1)
			return (ft_print_error(RED "Error arguments" RESET), -1);
	}
	temp->stop = 0;
	*data = temp;
	return (0);
}

static int	ft_fork_init(t_data *data)
{
	int	i;

	data->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->num_of_forks);
	if (!data->mutex_fork)
		return (ft_print_error(RED "Malloc error (forks)" RESET), -1);
	i = -1;
	while (++i < data->num_of_forks)
	{
		if (pthread_mutex_init(&data->mutex_fork[i], NULL) != 0)
			return (ft_print_error(RED "Error thread forks" RESET));
	}
	return (0);
}

static void ft_init(t_philo *philo, int i, t_data *data, pthread_mutex_t *forks)
{
	philo->index = i + 1;
	philo->num_eat_count = 0;
	philo->time_meal = 0;
	philo->data = data;
	if (i == 0)
	{
		philo->left_fork = forks + data->num_of_philos - 1;
		philo->right_fork = forks + i; 
	}
	else
	{
		philo->left_fork = forks + i + 1;
		philo->right_fork = forks + i;
	}
}

int	ft_init_philos(t_philo **philo, int ac, char **av)
{
	t_data	*data;
	t_philo	*temp;
	int		i;

	if (ft_init_data(&data, ac, av) == -1)
		return (-1);
	if (pthread_mutex_init(&data->mutex_print, NULL) != 0)
		return (ft_print_error(RED "Error thread print" RESET));
	if (ft_fork_init(data) == -1)
		return (-1);
	temp = (t_philo *)malloc(sizeof(t_philo) * data->num_of_philos);
	if (!temp)
		return (ft_print_error(RED "Malloc error (philos)" RESET), -1);
	i = -1;
	while (++i < data->num_of_philos)
		ft_init(temp + i, i, data, data->mutex_fork);
	*philo = temp;
	return (0);
}
