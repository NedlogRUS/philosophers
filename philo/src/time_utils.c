/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:11:35 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/15 19:40:40 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(t_data *ph)
{
	struct timeval	time;
	long long		out;

	(void) ph;
	gettimeofday(&time, NULL);
	out = (time.tv_sec * 1000 + time.tv_usec / 1000);
	return (out);
}

long long	get_curr_time(t_data *ph)
{
	struct timeval	time;
	long long		out;

	gettimeofday(&time, NULL);
	out = (time.tv_sec * 1000 + time.tv_usec / 1000) - ph->s_time;
	return (out);
}

void	ph_usleep(int ms, t_data *ph)
{
	long long	start;

	start = get_time(ph);
	while ((get_time(ph) - start) < ms)
		usleep(ms / 10);
	return ;
}
