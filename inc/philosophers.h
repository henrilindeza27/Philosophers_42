/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:17:33 by hlindeza          #+#    #+#             */
/*   Updated: 2023/10/07 14:55:28 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_geral	t_geral;

typedef struct s_philo
{
	int					id;

	size_t				last_meal;
	size_t				start_time;

	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;

	pthread_t			thread;
	t_geral				*p_geral;

	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;

}						t_philo;

typedef struct s_geral
{
	int					nbr_of_philos;
	int					nbr_of_meals;
	int					flag;

	pthread_mutex_t		write;
	pthread_mutex_t		w8;
	pthread_mutex_t		*forks;

	t_philo				*philos;
}						t_geral;

// init.c
void					init_all(t_geral *geral, char **argv);

// checks.c
void					check_args(int argc, char **argv);
int						is_dead(t_philo *philo);

// aux_functions.c
long					ft_atoi(char *str);
size_t					get_time(void);
void					destroy_all(t_geral *geral);
void					print_message(size_t time, char *str, t_philo *philo);
void					take_forks(t_philo *philo);

// philo.c
void					lock_left_fork(t_philo *philo);
void					lock_right_fork(t_philo *philo);
void					think(t_philo *philo);
void					ft_sleep(t_philo *philo);
void					eat(t_philo *philo);

// more_functions.c
void					ft_error(char *txt);
void					*philo(void *arg);
void					aux_eat(t_philo *philo);

#endif
