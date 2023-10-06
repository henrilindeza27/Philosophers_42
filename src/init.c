/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:53:43 by hlindeza          #+#    #+#             */
/*   Updated: 2023/10/06 17:56:28 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	init_philos(t_geral *geral, char **argv)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		geral->philos[i].id = i + 1;
		geral->philos[i].p_geral = geral;
		geral->philos[i].last_meal = 0;
		geral->philos[i].time_to_die = ft_atoi(argv[2]);
		geral->philos[i].time_to_eat = ft_atoi(argv[3]);
		geral->philos[i].time_to_sleep = ft_atoi(argv[4]);
		geral->philos[i].start_time = get_time();
		geral->philos[i].left_fork = &geral->forks[i];
		if (i == 0)
			geral->philos[i].right_fork = &geral->forks[ft_atoi(argv[1]) - 1];
		else
			geral->philos[i].right_fork = &geral->forks[i - 1];
		pthread_create(&geral->philos[i].thread, NULL, (void *)philo,
			&geral->philos[i]);
	}
}

static void	init_forks(t_geral *geral)
{
	int	i;

	i = -1;
	while (++i < geral->nbr_of_philos)
		pthread_mutex_init(&geral->forks[i], NULL);
}

void	init_all(t_geral *geral, char **argv)
{
	if (argv[5])
		geral->nbr_of_meals = ft_atoi(argv[5]) * ft_atoi(argv[1]);
	else
		geral->nbr_of_meals = -1;
	init_forks(geral);
	init_philos(geral, argv);
}