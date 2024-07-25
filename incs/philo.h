/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:05:18 by vkettune          #+#    #+#             */
/*   Updated: 2024/07/25 13:46:01 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef enum e_status
{
	EAT,
	SLEEP,
	THINK,
	FORK
}	t_status;

typedef struct s_data
{
	int				philo_count;
	int				meal_count;
	int				full_philos;
	size_t			start_time;
	size_t			meal_time;
	size_t			sleep_time;
	size_t			death_time;
	t_philo			*philo;
	pthread_mutex_t	philo_mutex;
	pthread_mutex_t	*fork_lock;
	int				end;
}	t_data;

typedef struct s_philo
{
	int					id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					meals_eaten;
	size_t				last_meal_time;
	t_data				*data;
}	t_philo;

int			destroy_all_mutexes(t_data *data);

int			error(char *str);

int			check_max_int(char **input);
int			input_check(int argc, char **input);
int			philo_init(t_data *data, t_philo *philo);
int			data_init(t_data *data, char **argv);

int			main(int argc, char **argv);

int			check_if_philos_exist(t_data *data);
int			check_if_full(t_data *data);

void		philo_actions(t_data *data, t_philo *philo, t_status status);
int			fork_distribution(t_data *data, t_philo *philo);
int			philo_eat(t_data *data, t_philo *philo);
int			philo_sleep(t_data *data, t_philo *philo);

size_t		get_current_time(void);
void		ft_usleep(t_data *data, size_t time_ms);

void		*philo_routine(void *arg);
void		*philo_monitor(t_data *data, pthread_t *threads);
int			philo_start(t_data *data, t_philo *philo);
int			are_philos_full(t_data *data);

void		eaten_enough(t_data *data, t_philo *philo);
int			philo_has_died(t_data *data, t_philo *philo);
int			if_is_dead(t_data *data, t_philo *philo);

int			set_data_mutex(t_data *data);
int			ft_atoi(char *str);
void		join_threads(pthread_t	*threads, int count);
int			ft_isdigit(char *str);

#endif