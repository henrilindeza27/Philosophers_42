/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:18:13 by hlindeza          #+#    #+#             */
/*   Updated: 2023/10/06 17:56:43 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	is_number(char *nbr)
{
	int	i;

	i = -1;
	if (nbr[i] == '+' || nbr[i] == '-')
		i++;
	while (nbr[++i])
	{
		if (!(nbr[i] >= '0' && nbr[i] <= '9'))
			return (0);
	}
	return (1);
}

void	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		ft_error("Error, out of range for args");
	i = 0;
	while (argv[++i])
	{
		if (ft_atoi(argv[i]) <= 0)
			ft_error("Error, only positive nbr are valide");
		if (!(is_number(argv[i])))
			ft_error("Error, not only numbers on args");
		if (ft_atoi(argv[i]) > 2147483647)
			ft_error("Error, obove INT_MAX");
	}
}

int	is_dead(t_philo *philo)
{
	unsigned long	current_time;

	pthread_mutex_lock(&philo->p_geral->w8);
	if (philo->p_geral->flag == 1)
	{
		pthread_mutex_unlock(&philo->p_geral->w8);
		return (1);
	}
	current_time = get_time();
	if ((current_time - philo->last_meal) >= (philo->time_to_die))
	{
		philo->p_geral->flag = 1;
		print_message(philo->last_meal, "died", philo);
		pthread_mutex_unlock(&philo->p_geral->w8);
		return (1);
	}
	pthread_mutex_unlock(&philo->p_geral->w8);
	return (0);
}
