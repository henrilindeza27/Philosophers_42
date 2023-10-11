/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:12:43 by hlindeza          #+#    #+#             */
/*   Updated: 2023/10/11 00:57:34 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

void	*philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->geral->nbr_of_philos == 1)
	{
		print_message("has taken a fork", philo, 1);
		ft_usleep(philo->geral->time_to_die);
	}
	if (philo->geral->nbr_of_philos > 1 && philo->id % 2)
		ft_usleep(40);
	while (check_flag(philo->geral))
	{
		if (philo->id % 2)
			usleep(100);
		if (philo->geral->nbr_of_meals > 0
			&& philo->meals_eaten >= philo->geral->nbr_of_meals)
			break ;
		eat(philo);
		pthread_mutex_unlock(&philo->geral->forks[philo->left_hand]);
		pthread_mutex_unlock(&philo->geral->forks[philo->right_hand]);
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_geral	geral;

	if (argc >= 5 && argc <= 6)
	{
		if (check_args(&geral, argv))
			return (-1);
		if (init_all(&geral))
			return (-1);
		check_dead(&geral);
		destroy_all(&geral);
	}
	return (0);
}
