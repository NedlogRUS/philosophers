/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:31:29 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/15 19:38:14 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	hand_out_forks(t_data *ph, t_phil *phils)
{
	if (phils->num == 0)
		phils->left_fork = &ph->m_forks[phils->num];
	else
		phils->left_fork = &ph->m_forks[phils->num - 1];
	if (phils->num == 0)
		phils->right_fork = &ph->m_forks[ph->num_of_philo - 1];
	else
		phils->right_fork = &ph->m_forks[phils->num];
}

void	initialize_forks(t_data *ph)
{
	int	i;

	i = 0;
	ph->m_forks = malloc(sizeof(pthread_mutex_t) * ph->num_of_philo);
	while (i <= ph->num_of_philo - 1)
	{
		pthread_mutex_init(&(ph->m_forks[i]), 0);
		i++;
	}
}

void	initialize_data(t_data *ph, int ac, char **av)
{
	ph->num_of_philo = ph_atoi(av[1]);
	ph->time_to_die = ph_atoi(av[2]);
	ph->time_to_eat = ph_atoi(av[3]) * 1000;
	ph->time_to_sleep = ph_atoi(av[4]) * 1000;
	if (ac == 6)
		ph->limit_of_eat = ph_atoi(av[5]);
	else
		ph->limit_of_eat = 0;
	ph->must_die = 0;
	ph->s_time = get_time(ph);
	pthread_mutex_init(&(ph->m_printf), 0);
	pthread_mutex_init(&(ph->m_must_die), 0);
}

void	initialize_philos(t_data *ph)
{
	int		i;

	i = 0;
	ph->phils = malloc(sizeof(t_phil) * ph->num_of_philo);
	while (i <= ph->num_of_philo - 1)
	{
		ph->phils[i].num = i;
		ph->phils[i].last_eat = get_curr_time(ph);
		ph->phils[i].data = ph;
		ph->phils[i].eat_counter = 0;
		hand_out_forks(ph, &ph->phils[i]);
		pthread_mutex_init(&(ph->phils[i].m_last_eat), 0);
		pthread_mutex_init(&(ph->phils[i].m_eat_counter), 0);
		i++;
	}
}

int	initialization(t_data *ph, int ac, char **av)
{
	if (check_args(ac, av))
		return (1);
	initialize_data(ph, ac, av);
	initialize_forks(ph);
	initialize_philos(ph);
	return (0);
}
