/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:37:28 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/08 19:02:13 by apanikov         ###   ########.fr       */
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
	long long			start_time;
	struct s_phil		*phils;
	pthread_mutex_t		mutex_stdout;
	pthread_mutex_t		*mutex_forks;
	pthread_mutex_t		mutex_flag_die;
	int					philo_die;
}					t_data;

typedef struct s_phil
{
	struct s_data	*data;
	int				num;
	pthread_t		forks;
	long long		last_eat;
	int				is_dead;
	int				finished_eating;
	int				flag_finished;
	pthread_mutex_t	mutex_last_meal;
	pthread_mutex_t	mutex_eating;
}					t_phil;

int	check_args(int ac, char **av);
int	ph_atoi(const char *str);

#endif