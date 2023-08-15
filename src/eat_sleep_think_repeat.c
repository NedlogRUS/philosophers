/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think_repeat.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:37:58 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/15 19:35:45 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	phil_eat(t_phil	*phil)
{
	if (phil->data->num_of_philo == 1)
		return (chosen_one(phil), 0);
	pthread_mutex_lock(phil->left_fork);
	if (!check_die(phil))
		return (unlock_m_forks(phil, 1), 0);
	pthread_mutex_lock(phil->right_fork);
	if (!check_die(phil))
		return (unlock_m_forks(phil, 2), 0);
	pthread_mutex_lock(&phil->data->m_printf);
	printf("Time: %lldms Philo: %d has taken a forks\n", \
		get_curr_time(phil->data), phil->num + 1);
	printf("Time: %lldms Philo: %d is eating\n", \
		get_curr_time(phil->data), phil->num + 1);
	pthread_mutex_unlock(&phil->data->m_printf);
	ph_usleep(phil->data->time_to_eat / 1000, phil->data);
	pthread_mutex_lock(&phil->m_last_eat);
	phil->last_eat = get_curr_time(phil->data);
	pthread_mutex_unlock(&phil->m_last_eat);
	pthread_mutex_unlock(phil->left_fork);
	pthread_mutex_unlock(phil->right_fork);
	pthread_mutex_lock(&phil->m_eat_counter);
	phil->eat_counter++;
	pthread_mutex_unlock(&phil->m_eat_counter);
	return (1);
}

void	phil_sleep(t_phil	*phil)
{
	pthread_mutex_lock(&phil->data->m_printf);
	printf("Time: %lldms Philo: %d is sleeping\n", \
		get_curr_time(phil->data), phil->num + 1);
	pthread_mutex_unlock(&phil->data->m_printf);
	ph_usleep(phil->data->time_to_sleep / 1000, phil->data);
}
