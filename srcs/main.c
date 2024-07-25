/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:04:52 by vkettune          #+#    #+#             */
/*   Updated: 2024/07/25 13:43:46 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		ret;

	if (argc < 5 || argc > 6)
		return (error("Invalid number of arguments"));
	if (input_check(argc, argv) == 1 || data_init(&data, argv) == 1)
		return (1);
	data.philo = malloc(data.philo_count * sizeof(t_philo));
	if (!data.philo)
		return (destroy_all_mutexes(&data));
	if (philo_init(&data, data.philo) != 0)
	{
		destroy_all_mutexes(&data);
		free(data.philo);
		return (1);
	}
	ret = philo_start(&data, data.philo);
	destroy_all_mutexes(&data);
	free(data.philo);
	if (ret == 1)
		return (1);
	return (0);
}
