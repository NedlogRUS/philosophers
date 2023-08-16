/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:56:25 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/15 19:23:48 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_atoi(const char *str)
{
	long long	out;
	int			i;

	out = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		out = out * 10 + str[i] - '0';
		i++;
		if (out > 2147483647)
			return (-1);
	}
	return ((int)out);
}

int	check_max(char *av)
{
	int	i;

	i = ph_atoi(av);
	if (i == -1 || i == 0)
		return (1);
	return (0);
}

int	check_num(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] < '0' || av[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (1);
	while (i < ac)
	{
		if (check_num(av[i]))
			return (1);
		else if (check_max(av[i]))
			return (1);
		i++;
	}
	return (0);
}
