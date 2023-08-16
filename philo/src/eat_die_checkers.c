/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_die_checkers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:42:32 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/15 19:32:43 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die_one_time(t_data *ph)
{
	pthread_mutex_lock(&ph->m_must_die);
	ph->must_die = 1;
	pthread_mutex_unlock(&ph->m_must_die);
}

void	die_two_time(t_data *ph, int i)
{
	pthread_mutex_lock(&ph->m_printf);
	printf("Time: %lldms Philo: %d is die\n", \
		get_curr_time(ph), ph->phils[i].num + 1);
	pthread_mutex_unlock(&ph->m_printf);
	die_one_time(ph);
	pthread_mutex_unlock(&ph->phils[i].m_last_eat);
}

void	*die_checker(void *p)
{
	t_data	*ph;
	int		i;

	ph = (t_data *) p;
	while (1)
	{
		i = 0;
		while (i <= ph->num_of_philo - 1)
		{
			if (!check_die(&ph->phils[i]))
				return (NULL);
			pthread_mutex_lock(&ph->phils[i].m_last_eat);
			if (ph->time_to_die < (get_curr_time(ph) - ph->phils[i].last_eat))
				return (die_two_time(ph, i), NULL);
			else
				pthread_mutex_unlock(&ph->phils[i].m_last_eat);
			i++;
		}
	}
	return (NULL);
}

int	eat_checker_2(t_data *ph, int *i)
{
	if (!check_die(&ph->phils[*i]))
		return (0);
	pthread_mutex_lock(&ph->phils[*i].m_eat_counter);
	if (ph->phils[*i].eat_counter < ph->limit_of_eat)
	{
		pthread_mutex_unlock(&ph->phils[*i].m_eat_counter);
		return (1);
	}
	pthread_mutex_unlock(&ph->phils[*i].m_eat_counter);
	if (*i == ph->num_of_philo - 1)
		return (die_one_time(ph), 0);
	pthread_mutex_lock(&ph->phils[*i].m_eat_counter);
	if (ph->phils[*i].eat_counter >= ph->limit_of_eat)
	{
		*i += 1;
		pthread_mutex_unlock(&ph->phils[*i - 1].m_eat_counter);
	}
	else
		pthread_mutex_unlock(&ph->phils[*i].m_eat_counter);
	return (1);
}

void	*eat_checker(void *p)
{
	t_data	*ph;
	int		i;

	ph = (t_data *) p;
	i = 0;
	while (1)
	{
		while (i <= ph->num_of_philo - 1)
		{
			if (!eat_checker_2(ph, &i))
				return (NULL);
			break ;
		}
	}
	return (NULL);
}
