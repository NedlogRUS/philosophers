/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:41:26 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/15 19:26:14 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_die(t_phil *phil)
{
	pthread_mutex_lock(&phil->data->m_must_die);
	if (phil->data->must_die == 1)
	{
		pthread_mutex_unlock(&phil->data->m_must_die);
		return (0);
	}
	pthread_mutex_unlock(&phil->data->m_must_die);
	return (1);
}

void	unlock_m_forks(t_phil *phil, int i)
{
	if (i == 1)
	{
		pthread_mutex_unlock(phil->left_fork);
		return ;
	}
	if (i == 2)
	{
		pthread_mutex_unlock(phil->left_fork);
		pthread_mutex_unlock(phil->right_fork);
		return ;
	}	
}
