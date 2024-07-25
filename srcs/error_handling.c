/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 04:08:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/07/25 08:03:02 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *str)
{
	printf("Error: %s\n", str);
	return (1);
}

int	destroy_all_mutexes(t_data *data, int i, int check) // remove i
{
	t_philo	*philo;
	// int i;

	philo = data->philo;
	i = 0;
	if (check == 1)
	{
		while (i < data->philo_count)
		{
			pthread_mutex_destroy(&data->fork_lock[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&data->philo_mutex);
	free(data->fork_lock);
	return (1);
}
