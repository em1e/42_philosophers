/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:40:20 by vkettune          #+#    #+#             */
/*   Updated: 2024/07/25 15:16:15 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_max_int(char **input)
{
	int	i;
	int	max;
	int	check;

	i = 1;
	max = 2147483647;
	while (input[i])
	{
		check = ft_atoi(input[i]);
		if (check <= 0 || check > max)
			return (1);
		i++;
	}
	return (0);
}

int	input_check(int argc, char **input)
{
	if (argc == 5 || argc == 6)
	{
		if (ft_isdigit(input[1]) == 1)
			return (error("Invalid input: Number of philos"));
		if (ft_isdigit(input[2]) == 1)
			return (error("Invalid input: Time to die"));
		if (ft_isdigit(input[3]) == 1)
			return (error("Invalid input: Time to eat"));
		if (ft_isdigit(input[4]) == 1)
			return (error("Invalid input: Time to sleep"));
		if (argc == 6 && ft_isdigit(input[5]) == 1)
			return (error("Invalid input: Meals to eat"));
		if (check_max_int(input) == 1)
			return (error("Invalid input: One of the numbers is invalid"));
	}
	return (0);
}

int	philo_init(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		philo[i].id = i + 1;
		philo[i].last_meal_time = data->start_time;
		philo[i].meals_eaten = 0;
		philo[i].data = data;
		philo[i].right_fork = &data->fork_lock[i];
		philo[i].left_fork = &data->fork_lock[(i + 1) % data->philo_count];
		i++;
	}
	return (0);
}

int	set_data_mutex(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->philo_mutex, NULL) != 0)
		return (1);
	data->fork_lock = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (data->fork_lock == NULL)
		return (1);
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->fork_lock[i], NULL) != 0)
			return (destroy_all_mutexes(data));
		i++;
	}
	return (0);
}

int	data_init(t_data *data, char **argv)
{
	data->philo_count = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->meal_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->meal_count = -1;
	if (argv[5])
		data->meal_count = ft_atoi(argv[5]);
	data->full_philos = 0;
	data->end = 0;
	data->start_time = get_current_time();
	if (set_data_mutex(data) == 1)
		return (1);
	return (0);
}
