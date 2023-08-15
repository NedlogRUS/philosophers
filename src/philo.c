/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:35:12 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/15 19:25:55 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	chosen_one(t_phil	*phil)
{
	usleep(phil->data->time_to_eat);
	return ;
}

void	*phil_life(void *p)
{
	t_phil	*phil;

	phil = (t_phil *) p;
	pthread_mutex_lock(&phil->m_last_eat);
	phil->last_eat = get_curr_time(phil->data);
	pthread_mutex_unlock(&phil->m_last_eat);
	if (phil->num % 2 != 0)
		usleep(2500);
	while (1)
	{
		if (!phil_eat(phil))
			return (NULL);
		if (!check_die(phil))
			return (NULL);
		phil_sleep(phil);
		if (!check_die(phil))
			return (NULL);
		pthread_mutex_lock(&phil->data->m_printf);
		printf("Time: %lldms Philo: %d is thinking\n", \
			get_curr_time(phil->data), phil->num + 1);
		pthread_mutex_unlock(&phil->data->m_printf);
		if (!check_die(phil))
			return (NULL);
	}
	return (NULL);
}

void	start_philo(t_data *ph)
{
	int	i;

	i = 0;
	while (i <= ph->num_of_philo - 1)
	{
		pthread_create(&ph->phils[i].thread, 0, &phil_life, &ph->phils[i]);
		i++;
	}
	pthread_create(&ph->die_check, 0, &die_checker, ph);
	if (ph->limit_of_eat > 0)
		pthread_create(&ph->eat_check, 0, &eat_checker, ph);
	i = 0;
	while (i <= ph->num_of_philo - 1)
	{
		pthread_join(ph->phils[i].thread, 0);
		i++;
	}
	pthread_join(ph->die_check, 0);
	if (ph->limit_of_eat > 0)
		pthread_join(ph->eat_check, 0);
}
