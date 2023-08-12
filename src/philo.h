/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:37:28 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/13 00:47:00 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdint.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_data
{
	int					num_of_philo;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					limit_of_eat;
	long long			s_time;
	int					must_die;
	pthread_t			die_check;
	pthread_mutex_t		m_printf;
	pthread_mutex_t		m_must_die;
	pthread_mutex_t		*m_forks;
	struct s_phil		*phils;
}					t_data;

typedef struct s_phil
{
	int				num;
	pthread_t		thread;
	long long		last_eat;
	int				is_dead;
	int				finished_eating;
	int				flag_finished;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	m_last_eat;
	struct s_data	*data;
}					t_phil;

int	check_args(int ac, char **av);
int	ph_atoi(const char *str);

#endif