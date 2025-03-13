/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_av.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:52:16 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/13 14:16:12 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_is_numeric(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '\0')
	{
		if (av[i] < 48 || av[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

int	ft_atol_av(const char *str)
{
	long long	result;
	int			sign;
	int			i;

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
		i++;
	}
	return (result * sign);
}

int	ft_check_av(char **av)
{
	if (ft_atol_av(av[1]) > MAX_PHILO || ft_atol_av(av[1]) <= 0
		|| ft_is_numeric(av[1]) == 1)
		return (ft_print_error(RED "[Invalid number of philo]" RESET), 1);
	if (ft_atol_av(av[2]) <= 0 || ft_is_numeric(av[2]) == 1)
		return (ft_print_error(RED "[Invalid time to die]" RESET), 1);
	if (ft_atol_av(av[3]) <= 0 || ft_is_numeric(av[3]) == 1)
		return (ft_print_error(RED "[Invalid time to eat]" RESET), 1);
	if (ft_atol_av(av[4]) <= 0 || ft_is_numeric(av[4]) == 1)
		return (ft_print_error(RED "[Invalid time to sleep]" RESET), 1);
	if (av[5] && (ft_atol_av(av[5]) < 0 || ft_is_numeric(av[5]) == 1))
		return (ft_print_error(RED "[Invalid number of meal]" RESET), 1);
	return (0);
}
