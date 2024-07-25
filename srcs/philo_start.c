/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 07:28:28 by vkettune          #+#    #+#             */
/*   Updated: 2024/07/25 13:32:18 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	
	if (philo->id % 2 == 0)
	{
		philo_actions(philo->data, philo, THINK);
		ft_usleep(philo->data, philo->data->meal_time / 2); // does nothing
	}
	while (!check_if_philos_exist(philo->data))
	{
		if (philo_eat(philo->data, philo) == 1)
			break ;
		if (check_if_philos_exist(philo->data))
			break;
		philo_sleep(philo->data, philo);
		if (check_if_philos_exist(philo->data))
			break;
		philo_actions(philo->data, philo, THINK);
	}
	return (NULL);
}

void	*philo_monitor(t_data *data, pthread_t	*threads)
{
	while (1)
	{
		usleep(42);
		eaten_enough(data, data->philo);
		if (if_is_dead(data, data->philo)
			|| are_philos_full(data))
			break ;
	}
	join_threads(threads, data->philo_count);
	return (NULL);
}

int	philo_start(t_data *data, t_philo *philo)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(data->philo_count * sizeof(pthread_t));
	if (threads == 0)
		return (-1);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(threads + i, NULL, &philo_routine, &philo[i]) == -1)
		{
			printf("Error creating thread\n");
			join_threads(threads, i + 1);
			free(threads);
			return (-1);
		}
		i++;
	}
	philo_monitor(data, threads);
	free(threads);
	return (0);
}
