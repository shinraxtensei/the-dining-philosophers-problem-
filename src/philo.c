/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:47:05 by ahouari           #+#    #+#             */
/*   Updated: 2022/03/04 08:50:17 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(int error)
{
	if (error == 1)
		printf("Wrong amount of args.\n");
	else if (error == 2)
		printf("Error while parsing.\n");
	else if (error == 3)
		printf("Error while creating threads.\n");
	return ;
}

void	destroy_philos(t_data *data, t_philos *philo)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
		pthread_join(philo[i].philo_thread, NULL);
	i = -1;
	while (++i < data->nb_philos)
		pthread_mutex_destroy(&data->fork_mutex[i]);
	pthread_mutex_destroy(&data->action_mutex);
}

int	init_routine(t_data *data)
{
	int			i;
	t_philos	*philo;

	i = 0;
	philo = data->philos;
	data->time_birth = timestamp();
	while (i < data->nb_philos)
	{
		if (pthread_create(&philo[i].philo_thread, NULL, &routine, &philo[i]))
			return (false);
		philo[i].time_eat = timestamp();
		i++;
	}
	dead_check(data, data->philos);
	destroy_philos(data, philo);
	return (true);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (error(1), false);
	if (!(parse_all(&data, av)))
		return (error(2), false);
	if (!(init_routine(&data)))
		return (error(3), false);
	return (true);
}