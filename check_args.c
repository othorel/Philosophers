/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:07:53 by olthorel          #+#    #+#             */
/*   Updated: 2025/01/19 15:07:53 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_av_numeric(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isnumeric(av[i]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_nb_philo(char *av)
{
	int	nb_philo;

	nb_philo = ft_atoi(av);
	if (nb_philo <= 0)
		return (0);
	return (1);
}

static int	check_time(char **av)
{
	int	i;
	int	time;

	i = 2;
	while (i <= 4)
	{
		time = ft_atoi(av[i]);
		if (time <= 0)
			return (0);
		i++;
	}
	return (1);	
}

static int check_must_eat(int ac, char *av)
{
	int	must_eat;

	if (ac == 6)
	{
		must_eat = ft_atoi(av);
		if (must_eat <= 0)
			return (0);
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (ft_putstr_fd("Error: invalid number of arguments\n", 2), 0);
	else if (!check_av_numeric(av))
		return (ft_putstr_fd("Error: arguments must be numeric\n", 2), 0);
	else if (!check_nb_philo(av[1]))
		return (ft_putstr_fd("Error: invalid number of philosophers\n", 2), 0);
	else if (!check_time(av))
		return (ft_putstr_fd("Error: invalid time\n", 2), 0);
	else if (!check_must_eat(ac, av[5]))
		return (ft_putstr_fd("Error: invalid number of meals\n", 2), 0);
	return (1);	
}
