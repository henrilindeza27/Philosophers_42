/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:57:52 by hlindeza          #+#    #+#             */
/*   Updated: 2023/10/06 17:58:02 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	lock_left_fork(t_philo *philo)
{
	unsigned long	current_time;

	pthread_mutex_lock(philo->left_fork);
	if (!is_dead(philo))
		print_message(philo->start_time, "has taken a fork", philo);
}

void	lock_right_fork(t_philo *philo)
{
	unsigned long	current_time;

	pthread_mutex_lock(philo->right_fork);
	if (!is_dead(philo))
		print_message(philo->start_time, "has taken a fork", philo);
}

void	think(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	print_message(philo->start_time, "is thinking", philo);
}
void	ft_sleep(t_philo *philo)
{
	size_t	time;

	if (!is_dead(philo))
	{
		print_message(philo->start_time, "is sleeping", philo);
		time = get_time();
		while ((get_time() - time) < philo->time_to_sleep)
		{
			if (is_dead(philo))
				return ;
			usleep(1);
		}
	}
}

void	eat(t_philo *philo)
{
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	if (philo->p_geral->nbr_of_philos == 1)
	{
		print_message(philo->start_time, "has taken a fork", philo);
		usleep(philo->time_to_die * 1000);
		return ;
	}
	print_message(philo->start_time, "is eating", philo);
	aux_eat(philo);
}
