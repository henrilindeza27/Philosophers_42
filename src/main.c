/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:10:29 by hlindeza          #+#    #+#             */
/*   Updated: 2023/10/06 18:01:20 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int argc, char **argv)
{
	t_geral	geral;

	check_args(argc, argv);
	geral.nbr_of_philos = ft_atoi(argv[1]);
	geral.philos = malloc(sizeof(t_philo) * geral.nbr_of_philos);
	geral.forks = malloc(sizeof(pthread_mutex_t) * geral.nbr_of_philos);
	if (!geral.philos || !geral.forks)
		return (0);
	geral.flag = 0;
	pthread_mutex_init(&geral.w8, NULL);
	pthread_mutex_init(&geral.write, NULL);
	init_all(&geral, argv);
	destroy_all(&geral);
	return (0);
}
