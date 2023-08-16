/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:36:57 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/16 21:07:32 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*ph;
	int		out;

	out = 0;
	ph = malloc(sizeof(t_data));
	if (!initialization(ph, ac, av))
	{
		start_philo(ph);
		while (waitpid(-1, &out, 0) != -1)
		{
			if (out / 256 == 1)
				kill_all(ph);
		}
	}
	else
	{
		write(2, "error\n", 6);
		return (1);
	}
	return (0);
}
