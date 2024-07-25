/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:52:06 by vkettune          #+#    #+#             */
/*   Updated: 2024/07/25 12:07:25 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eaten_enough(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	if (data->meal_count == -1)
		return ;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->philo_mutex);
		if (philo[i].meals_eaten == data->meal_count)
		{
			philo[i].meals_eaten++;
			data->full_philos++;
		}
		pthread_mutex_unlock(&data->philo_mutex);
		i++;
	}
}

int	are_philos_full(t_data *data)
{
	int	i;

	i = 0;
	
	if (!check_if_full(data))
	{
		while (i < data->philo_count)
		{
			pthread_mutex_lock(&data->philo_mutex);
			(data->philo + i++)->data.end = 1;
			pthread_mutex_unlock(&data->philo_mutex);
		}
		return (1);
	}
	return (0);
}

int	philo_has_died(t_data *data, t_philo *philo)
{
	size_t	time_since_meal;

	pthread_mutex_lock(&data->philo_mutex);
	time_since_meal = philo->last_meal_time;
	pthread_mutex_unlock(&data->philo_mutex);
	if (get_current_time() - time_since_meal > data->death_time)
		return (1);
	return (0);
}

int	if_is_dead(t_data *data, t_philo *philo)
{
	size_t	print_time;
	int		i;

	i = 0;
	print_time = get_current_time() - data->start_time;
	while (i < data->philo_count)
	{
		if (philo_has_died(data, &philo[i]))
		{
			pthread_mutex_lock(&data->philo_mutex);
			printf("%ld %d died\n", print_time, philo[i].id);
			pthread_mutex_unlock(&data->philo_mutex);
			i = 0;
			while (i < data->philo_count)
			{
				pthread_mutex_lock(&data->philo_mutex); // new
				(philo + i++)->data.end = 1;
				pthread_mutex_unlock(&data->philo_mutex); // new
			}
			return (1);
		}
		i++;
	}
	return (0);
}
