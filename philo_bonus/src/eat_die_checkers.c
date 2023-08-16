/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_die_checkers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:42:32 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/16 21:09:46 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_checker(t_phil *phil)
{
	if (phil->data->limit_of_eat > 0)
	{
		sem_wait(phil->data->sem_eat_counter);
		if (phil->eat_counter >= phil->data->limit_of_eat)
		{
			sem_post(phil->data->sem_eat_counter);
			exit (0);
		}
		else
			sem_post(phil->data->sem_eat_counter);
	}
}

void	*die_checker(void *p)
{
	t_phil	*phil;

	phil = (t_phil *) p;
	while (1)
	{
		eat_checker(phil);
		sem_wait(phil->data->sem_last_eat);
		if (phil->data->time_to_die < (get_curr_time(phil->data) \
			- phil->last_eat))
		{
			sem_wait(phil->data->sem_printf);
			printf("Time: %lldms Philo: %d is die\n", \
				get_curr_time(phil->data), phil->num + 1);
			sem_post(phil->data->sem_last_eat);
			exit (1);
		}
		else
			sem_post(phil->data->sem_last_eat);
	}
	return (NULL);
}
