/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:36:57 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/12 20:07:47 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_print(t_data *ph)
{
	printf("Number of Philosophers: %d\n", ph->num_of_philo);
	printf("Time to Die: %lld\n", ph->time_to_die);
	printf("Time to Eat: %lld\n", ph->time_to_eat);
	printf("Time to Sleep: %lld\n", ph->time_to_sleep);
	printf("Limit of Eat: %d\n", ph->limit_of_eat);
	printf("Start Time: %lld\n", ph->s_time);
	printf("\n");
}

void	check_print_philo(t_data *ph)
{
	int i = 0;
	while (i < ph->num_of_philo)
	{
	printf("Philosophers number: %d\n", ph->phils[i].num);
	printf("Last eat: %lld\n", ph->phils[i].last_eat);
	i++;
	}
}


long long	get_time(t_data *ph)
{
	(void) ph;
	struct timeval time;
	long long	out;
	
	gettimeofday(&time, NULL);
	out = (time.tv_sec * 1000 + time.tv_usec / 1000);
	return (out);
}

long long	get_curr_time(t_data *ph)
{
	struct timeval time;
	long long	out;
	
	gettimeofday(&time, NULL);
	out = (time.tv_sec * 1000 + time.tv_usec / 1000) - ph->s_time; 
	return (out);
}

void	initialize_forks(t_data *ph)
{
	int	i;

	i = 0;
	ph->m_forks = malloc(sizeof(pthread_mutex_t	) * ph->num_of_philo);
	while(i < ph->num_of_philo)
	{
		pthread_mutex_init(&(ph->m_forks[i]), 0);
		i++;
	}
}

void	initialize_data(t_data *ph, int ac, char **av)
{
	ph->num_of_philo = ph_atoi(av[1]);
	ph->time_to_die = ph_atoi(av[2]) * 1000;
	ph->time_to_eat = ph_atoi(av[3]) * 1000;
	ph->time_to_sleep = ph_atoi(av[4]) * 1000;
	if(ac == 6)
		ph->limit_of_eat = ph_atoi(av[5]);
	else
		ph->limit_of_eat = 0;
	ph->must_die = 0;
	ph->s_time = get_time(ph);
	pthread_mutex_init(&(ph->m_printf), 0);
}

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

void	initialize_philos(t_data *ph)
{
	int		i;

	ph->phils= malloc(sizeof(t_phil) * ph->num_of_philo);
	i = 0;
	while(i < ph->num_of_philo)
	{
		ph->phils[i].num = i;
		ph->phils[i].last_eat = get_curr_time(ph);
		ph->phils[i].is_dead = 0;
		// pthread_mutex_init(&(ph->phils[i].left_fork), 0);
		// pthread_mutex_init(&(ph->phils[i].right_fork), 0);
		ph->phils[i].data = ph;
		hand_out_forks(ph, &ph->phils[i]);
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
	// check_print(ph);
	// check_print_philo(ph);
	return (0);
}

void	phil_sleep(t_phil	*phil)
{
	pthread_mutex_lock(&phil->data->m_printf);
	printf("Time: %lldms Philo: %d is sleeping\n", get_curr_time(phil->data), phil->num + 1);
	pthread_mutex_unlock(&phil->data->m_printf);
	usleep(phil->data->time_to_sleep);
}

void	phil_eat(t_phil	*phil)
{
	pthread_mutex_lock(phil->left_fork);
	// printf("Time: %lldms Philo: %d has taken a left fork\n", get_curr_time(phil->data), phil->num + 1);
	pthread_mutex_lock(phil->right_fork);
	// printf("Time: %lldms Philo: %d has taken a right fork\n", get_curr_time(phil->data), phil->num + 1);
	pthread_mutex_lock(&phil->data->m_printf);
	printf("Time: %lldms Philo: %d has taken a forks\n", get_curr_time(phil->data), phil->num + 1);
	printf("Time: %lldms Philo: %d is eating\n", get_curr_time(phil->data), phil->num + 1);
	pthread_mutex_unlock(&phil->data->m_printf);
	usleep(phil->data->time_to_eat);
	pthread_mutex_unlock(phil->left_fork);
	pthread_mutex_unlock(phil->right_fork);
}

void	*phil_life(void *p)
{
	t_phil	*phil;

	phil = (t_phil *) p;
	while (1)
	{
		phil_eat(phil);
		phil_sleep(phil);
		pthread_mutex_lock(&phil->data->m_printf);
		printf("Time: %lldms Philo:%d is thinking\n", get_curr_time(phil->data), phil->num + 1);
		pthread_mutex_unlock(&phil->data->m_printf);
	}
	return	NULL;
}


void	start_philo(t_data *ph)
{
	int	i;

	i = 0;
	printf("CHECK\n");
	while (i < ph->num_of_philo)
	{
		pthread_create(&ph->phils[i].thread, 0, &phil_life, &ph->phils[i]);
		// printf("tread %d created\n", i);
		i++;
	}
	i = 0;
	while (i < ph->num_of_philo)
	{
		pthread_join(ph->phils[i].thread, 0);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data *ph;

	ph = malloc(sizeof(t_data));
	if (!initialization(ph, ac, av))
		start_philo(ph);
	else
		printf("error\n");
	free(ph);
} 
