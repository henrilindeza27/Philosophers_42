/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:10:29 by hlindeza          #+#    #+#             */
/*   Updated: 2023/10/11 00:58:18 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

int	check_flag(t_geral *geral)
{
	int	i;

	i = 1;
	pthread_mutex_lock(&geral->eating);
	if (geral->flag == 0)
		i = 0;
	pthread_mutex_unlock(&geral->eating);
	return (i);
}

static void	check_eatean(t_geral *geral)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&geral->w8);
	while (geral->nbr_of_meals && i < geral->nbr_of_philos
		&& geral->philos[i].meals_eaten >= geral->nbr_of_meals)
		i++;
	pthread_mutex_lock(&geral->eating);
	if (i >= geral->nbr_of_philos)
		geral->flag = 0;
	pthread_mutex_unlock(&geral->eating);
	pthread_mutex_unlock(&geral->w8);
}

static void	check_time_to_die(t_geral *geral)
{
	int		i;
	size_t	time;

	i = -1;
	while (++i < geral->nbr_of_philos && check_flag(geral))
	{
		pthread_mutex_lock(&geral->w8);
		time = get_time();
		if ((time - geral->philos[i].last_meal) >= geral->time_to_die)
		{
			print_message("died", &geral->philos[i], 0);
			pthread_mutex_lock(&geral->eating);
			geral->flag = 0;
			pthread_mutex_unlock(&geral->eating);
		}
		pthread_mutex_unlock(&geral->w8);
	}
}

void	check_dead(t_geral *geral)
{
	while (check_flag(geral))
	{
		check_eatean(geral);
		if (!check_flag(geral))
			break ;
		check_time_to_die(geral);
	}
}
