/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:36:57 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/09 19:53:14 by apanikov         ###   ########.fr       */
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

void	initialize_data(t_data *ph, int ac, char **av)
{
	ph->num_of_philo = ph_atoi(av[1]);
	ph->time_to_die = ph_atoi(av[2]);
	ph->time_to_eat = ph_atoi(av[3]);
	ph->time_to_sleep = ph_atoi(av[4]);
	if(ac == 6)
		ph->limit_of_eat = ph_atoi(av[5]);
	else
		ph->limit_of_eat = 0;
	ph->must_die = 0;
	ph->s_time = get_time(ph);
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
		pthread_mutex_init(&(ph->phils[i].left_fork), 0);
		pthread_mutex_init(&(ph->phils[i].right_fork), 0);
		i++;
	}
}

int	initialization(t_data *ph, int ac, char **av)
{
	if (check_args(ac, av))
		return (1);
	initialize_data(ph, ac, av);
	initialize_philos(ph);
	check_print(ph);
	check_print_philo(ph);
	return (0);
}

void	start_philo(t_data *ph)
{
	int	i;

	i = 0;
	while (i < ph->num_of_philo)
	{
		pthread_create(&ph->phils[i].thread, 0, phil_life, &ph->phils[i]);
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
