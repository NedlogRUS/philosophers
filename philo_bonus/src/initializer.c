/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:31:29 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/16 21:19:15 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_data(t_data *ph, int ac, char **av)
{
	ph->num_of_philo = ph_atoi(av[1]);
	ph->time_to_die = ph_atoi(av[2]);
	ph->time_to_eat = ph_atoi(av[3]) * 1000;
	ph->time_to_sleep = ph_atoi(av[4]) * 1000;
	if (ac == 6)
		ph->limit_of_eat = ph_atoi(av[5]);
	else
		ph->limit_of_eat = 0;
	ph->must_die = 0;
	ph->s_time = get_time(ph);
	sem_unlink("sem_forks");
	sem_unlink("sem_printf");
	sem_unlink("sem_last_eat");
	sem_unlink("sem_eat_counter");
	ph->sem_forks = sem_open("sem_forks", O_CREAT, 0666, ph->num_of_philo);
	ph->sem_printf = sem_open("sem_printf", O_CREAT, 0666, 1);
	ph->sem_last_eat = sem_open("sem_last_eat", O_CREAT, 0666, 1);
	ph->sem_eat_counter = sem_open("sem_eat_counter", O_CREAT, 0666, 1);
	if (ph->sem_forks == SEM_FAILED || ph->sem_printf == SEM_FAILED || \
		ph->sem_last_eat == SEM_FAILED || ph->sem_eat_counter == SEM_FAILED)
	{
		write(2, "error open_sem\n", 16);
		exit(1);
	}
}

void	initialize_philos(t_data *ph)
{
	int		i;

	i = 0;
	ph->phils = malloc(sizeof(t_phil) * ph->num_of_philo);
	while (i <= ph->num_of_philo - 1)
	{
		ph->phils[i].num = i;
		ph->phils[i].last_eat = get_curr_time(ph);
		ph->phils[i].data = ph;
		ph->phils[i].eat_counter = 0;
		ph->phils[i].pid = 0;
		i++;
	}
}

int	initialization(t_data *ph, int ac, char **av)
{
	if (check_args(ac, av))
		return (1);
	initialize_data(ph, ac, av);
	initialize_philos(ph);
	return (0);
}
