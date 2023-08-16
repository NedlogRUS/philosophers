/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think_repeat.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:37:58 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/16 18:37:09 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	phil_eat(t_phil	*phil)
{
	if (phil->data->num_of_philo == 1)
		chosen_one(phil);
	sem_wait(phil->data->sem_forks);
	sem_wait(phil->data->sem_forks);
	sem_wait(phil->data->sem_printf);
	printf("Time: %lldms Philo: %d has taken a forks\n", \
		get_curr_time(phil->data), phil->num + 1);
	printf("Time: %lldms Philo: %d is eating\n", \
		get_curr_time(phil->data), phil->num + 1);
	sem_post(phil->data->sem_printf);
	ph_usleep(phil->data->time_to_eat / 1000, phil->data);
	sem_wait(phil->data->sem_last_eat);
	phil->last_eat = get_curr_time(phil->data);
	sem_post(phil->data->sem_last_eat);
	sem_post(phil->data->sem_forks);
	sem_post(phil->data->sem_forks);
	sem_wait(phil->data->sem_eat_counter);
	phil->eat_counter++;
	sem_post(phil->data->sem_eat_counter);
}

void	phil_sleep(t_phil	*phil)
{
	sem_wait(phil->data->sem_printf);
	printf("Time: %lldms Philo: %d is sleeping\n", \
		get_curr_time(phil->data), phil->num + 1);
	sem_post(phil->data->sem_printf);
	ph_usleep(phil->data->time_to_sleep / 1000, phil->data);
}
