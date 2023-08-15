/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:37:28 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/15 19:34:04 by apanikov         ###   ########.fr       */
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
	pthread_t			eat_check;
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
	int				eat_counter;
	pthread_mutex_t	m_eat_counter;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	m_last_eat;
	struct s_data	*data;
}					t_phil;

int			check_args(int ac, char **av);
int			ph_atoi(const char *str);
long long	get_time(t_data *ph);
long long	get_curr_time(t_data *ph);
void		ph_usleep(int ms, t_data *ph);
int			initialization(t_data *ph, int ac, char **av);
void		start_philo(t_data *ph);
void		chosen_one(t_phil	*phil);
void		*eat_checker(void *p);
void		*die_checker(void *p);
int			phil_eat(t_phil	*phil);
void		phil_sleep(t_phil	*phil);
int			check_die(t_phil *phil);
void		unlock_m_forks(t_phil *phil, int i);

#endif