/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:12:12 by hlindeza          #+#    #+#             */
/*   Updated: 2023/10/11 20:33:31 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_geral	t_geral;

typedef struct s_philo
{
	int					left_hand;
	int					right_hand;

	int					id;
	int					meals_eaten;

	size_t				last_meal;

	pthread_t			thread;
	t_geral				*geral;
}						t_philo;

typedef struct s_geral
{
	int					nbr_of_philos;
	int					nbr_of_meals;
	int					flag;

	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				start_time;

	pthread_mutex_t		write;
	pthread_mutex_t		w8;
	pthread_mutex_t		eating;
	pthread_mutex_t		*forks;

	t_philo				*philos;
}						t_geral;

void					*philo(void *arg);

int						check_args(t_geral *geral, char **argv);
int						init_all(t_geral *geral);

long					ft_atoi(char *str);
size_t					get_time(void);
void					destroy_all(t_geral *geral);
void					print_message(char *str, t_philo *philo);
void					ft_usleep(size_t time);

void					lock_left_fork(t_philo *philo);
void					lock_right_fork(t_philo *philo);
void					think(t_philo *philo);
void					sleep_philo(t_philo *philo);
void					eat(t_philo *philo);

int						check_flag(t_geral *geral);
void					check_dead(t_geral *geral);
#endif