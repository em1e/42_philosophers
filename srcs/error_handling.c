/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mie <mie@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 04:08:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/07/26 11:19:23 by mie              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *str)
{
	printf("Error: %s\n", str);
	return (1);
}

int	destroy_all_mutexes(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->fork_lock[i]);
		i++;
	}
	pthread_mutex_destroy(&data->philo_mutex);
	free(data->fork_lock);
	return (1);
}
