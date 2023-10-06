/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:58:12 by hlindeza          #+#    #+#             */
/*   Updated: 2023/10/06 17:58:21 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_error(char *txt)
{
	printf("%s\n", txt);
	exit(1);
}

void	*philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_time();
	if (philo->id % 2 == 0)
		usleep(50);
	if (philo->p_geral->nbr_of_philos == 1)
		eat(philo);
	while (!is_dead(philo))
	{
		take_forks(philo);
		eat(philo);
		ft_sleep(philo);
		think(philo);
	}
	return (NULL);
}

void	aux_eat(t_philo *philo)
{
	size_t	time;

	time = get_time();
	while ((get_time() - time) < philo->time_to_eat)
	{
		if (is_dead(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return ;
		}
		usleep(1);
	}
	pthread_mutex_lock(&philo->p_geral->w8);
	philo->p_geral->nbr_of_meals--;
	if (philo->p_geral->nbr_of_meals == 0)
		philo->p_geral->flag = 1;
	pthread_mutex_unlock(&philo->p_geral->w8);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
