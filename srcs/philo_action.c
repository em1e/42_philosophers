/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 05:49:07 by vkettune          #+#    #+#             */
/*   Updated: 2024/07/25 12:55:25 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_actions(t_data *data, t_philo *philo, t_status status)
{
	size_t	time;
	
	time = get_current_time() - data->start_time;
	pthread_mutex_lock(&data->philo_mutex);
	if (status == EAT)
		printf("%lu %d is eating\n", time, philo->id);
	else if (status == SLEEP)
		printf("%lu %d is sleeping\n", time, philo->id);
	else if (status == THINK)
		printf("%lu %d is thinking\n", time, philo->id);
	else if (status == FORK)
		printf("%lu %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&data->philo_mutex);
}

int	fork_distribution(t_data *data, t_philo *philo)
{
	if (philo->id % 2)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	philo_actions(data, philo, FORK);
	if (data->philo_count == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	if (philo->id % 2)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	philo_actions(data, philo, FORK);
	return (0);
}

int	philo_eat(t_data *data, t_philo *philo)
{
	if (fork_distribution(data, philo) == 1)
		return (1);
	pthread_mutex_lock(&data->philo_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&data->philo_mutex);
	philo_actions(data, philo, EAT);
	ft_usleep(data, data->meal_time);
	pthread_mutex_lock(&data->philo_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->philo_mutex);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

void	philo_sleep(t_data *data, t_philo *philo)
{
	philo_actions(data, philo, SLEEP);
	ft_usleep(data, data->sleep_time);
}
