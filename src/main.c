/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:36:57 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/08 19:16:40 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_print(t_data *ph)
{
	printf("Number of Philosophers: %d\n", ph->num_of_philo);
	printf("Time to Die: %lld\n", ph->time_to_die);
	printf("Time to Eat: %lld\n", ph->time_to_eat);
	printf("Time to Sleep: %lld\n", ph->time_to_sleep);
	printf("Limit of Eat: %d\n", ph->limit_of_eat);
	printf("Start Time: %lld\n", ph->start_time);
	printf("Philosopher Die Flag: %d\n", ph->philo_die);
}

void	initialize_data(t_data *ph, int ac, char **av)
{
	ph->num_of_philo = ph_atoi(av[1]);
	ph->time_to_die = ph_atoi(av[2]);
	ph->time_to_eat = ph_atoi(av[3]);
	ph->time_to_sleep = ph_atoi(av[4]);
	if(ac == 6)
		ph->limit_of_eat = ph_atoi(av[5]);
	else
		ph->limit_of_eat = 0;
}

int	initialization(t_data *ph, int ac, char **av)
{
	if (check_args(ac, av))
		return (1);
	initialize_data(ph, ac, av);
	check_print(ph);
	return (0);
}

int	main(int ac, char **av)
{
	t_data *ph;

	ph = malloc(sizeof(t_data));
	if (!initialization(ph, ac, av))
		printf("ok\n");
	else
		printf("error\n");
	free(ph);
} 