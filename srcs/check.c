/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 07:28:28 by vkettune          #+#    #+#             */
/*   Updated: 2024/07/25 13:45:18 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_philos_exist(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->philo_mutex);
	ret = data->end;
	pthread_mutex_unlock(&data->philo_mutex);
	return (ret);
}

int	check_if_full(t_data *data)
{
	pthread_mutex_lock(&data->philo_mutex);
	if (data->full_philos >= data->philo_count)
	{
		pthread_mutex_unlock(&data->philo_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->philo_mutex);
	return (1);
}
