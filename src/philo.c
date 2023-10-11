/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:12:10 by hlindeza          #+#    #+#             */
/*   Updated: 2023/10/11 20:32:58 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

void	lock_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->geral->forks[philo->left_hand]);
	print_message("has taken a fork", philo);
}

void	lock_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->geral->forks[philo->right_hand]);
	print_message("has taken a fork", philo);
}

void	think(t_philo *philo)
{
	print_message("is thinking", philo);
}

void	sleep_philo(t_philo *philo)
{
	print_message("is sleeping", philo);
	ft_usleep(philo->geral->time_to_sleep);
}

void	eat(t_philo *philo)
{
	lock_right_fork(philo);
	lock_left_fork(philo);
	pthread_mutex_lock(&philo->geral->w8);
	print_message("is eating", philo);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->geral->w8);
	ft_usleep(philo->geral->time_to_eat);
	pthread_mutex_lock(&philo->geral->w8);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->geral->w8);
}
