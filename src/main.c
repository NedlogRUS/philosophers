/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:36:57 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/15 17:07:51 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	check_print(t_data *ph)
// {
// 	printf("Number of Philosophers: %d\n", ph->num_of_philo);
// 	printf("Time to Die: %lld\n", ph->time_to_die);
// 	printf("Time to Eat: %lld\n", ph->time_to_eat);
// 	printf("Time to Sleep: %lld\n", ph->time_to_sleep);
// 	printf("Limit of Eat: %d\n", ph->limit_of_eat);
// 	printf("Start Time: %lld\n", ph->s_time);
// 	printf("\n");
// }

// void	check_print_philo(t_data *ph)
// {
// 	int i = 0;
// 	while (i < ph->num_of_philo)
// 	{
// 	printf("Philosophers number: %d\n", ph->phils[i].num);
// 	printf("Last eat: %lld\n", ph->phils[i].last_eat);
// 	i++;
// 	}
// }


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

void	ph_usleep(int ms, t_data *ph)
{
	long long	start;

	start = get_time(ph);
	while ((get_time(ph) - start) < ms)
		usleep(ms / 10);
	return;
}

void	initialize_forks(t_data *ph)
{
	int	i;

	i = 0;
	ph->m_forks = malloc(sizeof(pthread_mutex_t	) * ph->num_of_philo);
	while(i <= ph->num_of_philo - 1)
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
	if(ac == 6)
		ph->limit_of_eat = ph_atoi(av[5]);
	else
		ph->limit_of_eat = 0;
	ph->must_die = 0;
	ph->s_time = get_time(ph);
	pthread_mutex_init(&(ph->m_printf), 0);
	pthread_mutex_init(&(ph->m_must_die), 0);
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

// void	hand_out_forks(t_data *ph, t_phil *phils) // ver 2.0
// {
// 	if (phils->num == 0)
// 		phils->left_fork = &ph->m_forks[phils->num + 1];
// 	else
// 		phils->left_fork = &ph->m_forks[phils->num];
// 	if (phils->num == 0)
// 		phils->right_fork = &ph->m_forks[phils->num];
// 	else if (phils->num == ph->num_of_philo - 1)
// 		phils->right_fork = &ph->m_forks[0];
// 	else
// 		phils->right_fork = &ph->m_forks[phils->num - 1];
// }

void	initialize_philos(t_data *ph)
{
	int		i;

	ph->phils= malloc(sizeof(t_phil) * ph->num_of_philo);
	i = 0;
	while(i <= ph->num_of_philo - 1)
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
	// check_print(ph);
	// check_print_philo(ph);
	return (0);
}

void	phil_sleep(t_phil	*phil)
{
	pthread_mutex_lock(&phil->data->m_printf);
	printf("Time: %lldms Philo: %d is sleeping\n", get_curr_time(phil->data), phil->num + 1);
	pthread_mutex_unlock(&phil->data->m_printf);
	ph_usleep(phil->data->time_to_sleep / 1000, phil->data);
}

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

void chosen_one(t_phil	*phil)
{
	usleep(phil->data->time_to_eat);
	return ;
}

int	phil_eat(t_phil	*phil)
{
	if(phil->data->num_of_philo == 1)
		return (chosen_one(phil), 0);
	pthread_mutex_lock(phil->left_fork);
	if (!check_die(phil))
		return (unlock_m_forks(phil, 1), 0);
	pthread_mutex_lock(phil->right_fork);
	if (!check_die(phil))
		return (unlock_m_forks(phil, 2), 0);
	pthread_mutex_lock(&phil->data->m_printf);
	printf("Time: %lldms Philo: %d has taken a forks\n", get_curr_time(phil->data), phil->num + 1);
	printf("Time: %lldms Philo: %d is eating\n", get_curr_time(phil->data), phil->num + 1);
	pthread_mutex_unlock(&phil->data->m_printf);
	ph_usleep(phil->data->time_to_eat / 1000, phil->data);
	pthread_mutex_lock(&phil->m_last_eat);
	phil->last_eat = get_curr_time(phil->data);
	pthread_mutex_unlock(&phil->m_last_eat);
	pthread_mutex_unlock(phil->left_fork);
	pthread_mutex_unlock(phil->right_fork);
	// if(phil->data->limit_of_eat > 0)
	// {
	// 	pthread_mutex_lock(&phil->m_eat_counter);
	// 	phil->eat_counter++;
	// 	printf("Phil: %d eat counter: %d\n", phil->num, phil->eat_counter);
	// 	pthread_mutex_unlock(&phil->m_eat_counter);
	// }
	pthread_mutex_lock(&phil->m_eat_counter);
	phil->eat_counter++;
	pthread_mutex_unlock(&phil->m_eat_counter);
	return (1);
}

void	*phil_life(void *p)
{
	t_phil	*phil;

	phil = (t_phil *) p;
	pthread_mutex_lock(&phil->m_last_eat);
	phil->last_eat = get_curr_time(phil->data);
	pthread_mutex_unlock(&phil->m_last_eat);
	// if (phil->num % 2 != 0)
	// 	usleep(2500);
	while (1)
	{
		if(!phil_eat(phil))
			return NULL;
		if (!check_die(phil))
			return NULL;
		phil_sleep(phil);
		if (!check_die(phil))
			return NULL;
		pthread_mutex_lock(&phil->data->m_printf);
		printf("Time: %lldms Philo: %d is thinking\n", get_curr_time(phil->data), phil->num + 1);
		pthread_mutex_unlock(&phil->data->m_printf);
		if (!check_die(phil))
			return NULL;
	}
	return	NULL;
}

void	*die_checker(void *p)
{
	t_data	*ph;
	int	i;


	ph = (t_data *) p;
	while (1)
	{
		i = 0;
		while (i <= ph->num_of_philo - 1)
		{
			pthread_mutex_lock(&ph->m_must_die);
			if (ph->must_die == 1)
			{
				pthread_mutex_unlock(&ph->m_must_die);
				return NULL;
			}
			pthread_mutex_unlock(&ph->m_must_die);
			pthread_mutex_lock(&ph->phils[i].m_last_eat);
			if (ph->time_to_die < (get_curr_time(ph) - ph->phils[i].last_eat))
			{
				pthread_mutex_lock(&ph->m_printf);
				printf("Time: %lldms Philo: %d is die\n", get_curr_time(ph), ph->phils[i].num + 1);
				pthread_mutex_unlock(&ph->m_printf);
				pthread_mutex_lock(&ph->m_must_die);
				ph->must_die = 1;
				pthread_mutex_unlock(&ph->m_must_die);
				pthread_mutex_unlock(&ph->phils[i].m_last_eat);
				return NULL;
			}
			else
			{
				pthread_mutex_unlock(&ph->phils[i].m_last_eat);
			}
			i++;
		}
	}
	return	NULL;
}

void	*eat_checker(void *p)
{
	t_data	*ph;
	int	i;

	ph = (t_data *) p;
	i = 0;
	while (1)
	{
		while (i <= ph->num_of_philo - 1)
		{
			pthread_mutex_lock(&ph->phils[i].m_eat_counter);
			if (ph->phils[i].eat_counter < ph->limit_of_eat)
			{
				pthread_mutex_unlock(&ph->phils[i].m_eat_counter);
				break;
			}
			pthread_mutex_unlock(&ph->phils[i].m_eat_counter);
			if (i == ph->num_of_philo - 1)
			{
				pthread_mutex_lock(&ph->m_must_die);
				ph->must_die = 1;
				pthread_mutex_unlock(&ph->m_must_die);
				return NULL;
			}
			pthread_mutex_lock(&ph->phils[i].m_eat_counter);
			if (ph->phils[i].eat_counter >= ph->limit_of_eat)
			{
				i++;
				pthread_mutex_unlock(&ph->phils[i - 1].m_eat_counter);
			}
			else
				pthread_mutex_unlock(&ph->phils[i].m_eat_counter);
		}
	}
	return	NULL;
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
	if(ph->limit_of_eat > 0)
		pthread_create(&ph->eat_check, 0, &eat_checker, ph);
	i = 0;
	while (i <= ph->num_of_philo - 1)
	{
		pthread_join(ph->phils[i].thread, 0);
		i++;
	}
	pthread_join(ph->die_check, 0);
	if(ph->limit_of_eat > 0)
		pthread_join(ph->eat_check, 0);
}

int	main(int ac, char **av)
{
	t_data *ph;

	ph = malloc(sizeof(t_data));
	if (!initialization(ph, ac, av))
		start_philo(ph);
	else
	{
		write(2,"error\n", 6);
		return (1);
	}
	return (0);
} 
