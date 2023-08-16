/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:35:12 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/16 21:06:11 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	chosen_one(t_phil	*phil)
{
	usleep(phil->data->time_to_eat);
	return ;
}

void	phil_life(t_phil *phil)
{
	sem_wait(phil->data->sem_last_eat);
	phil->last_eat = get_curr_time(phil->data);
	sem_post(phil->data->sem_last_eat);
	if (phil->num % 2 != 0)
		usleep(2500);
	while (1)
	{
		phil_eat(phil);
		phil_sleep(phil);
		sem_wait(phil->data->sem_printf);
		printf("Time: %lldms Philo: %d is thinking\n", \
			get_curr_time(phil->data), phil->num + 1);
		sem_post(phil->data->sem_printf);
	}
	return ;
}

void	kill_all(t_data *ph)
{
	int	i;

	i = 0;
	while (i <= ph->num_of_philo - 1)
	{
		kill(ph->phils[i].pid, SIGKILL);
		i++;
	}
	sem_post(ph->sem_printf);
}

void	start_philo(t_data *ph)
{
	int	i;
	int	out;

	i = 0;
	out = 0;
	while (i <= ph->num_of_philo - 1)
	{
		ph->phils[i].pid = fork();
		if (ph->phils[i].pid < 0)
		{
			write(2, "error open_fork\n", 16);
			exit(1);
		}
		if (ph->phils[i].pid == 0)
		{
			pthread_create(&ph->phils[i].checker, NULL, \
				die_checker, &ph->phils[i]);
			phil_life(&ph->phils[i]);
			pthread_join(ph->phils[i].checker, NULL);
		}
		i++;
	}
}
