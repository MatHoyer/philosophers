/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:57:11 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/15 12:09:20 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_state
{
	STATE_VIDE,
	STATE_DIED,
	STATE_THINKING,
	STATE_FORK,
	STATE_FORK_BIS,
	STATE_EATING,
	STATE_SLEEPING,
}					t_state;

typedef enum e_bool
{
	false,
	true,
}					t_bool;

typedef enum e_test
{
	TEST_CMP,
	TEST_MOD,
}					t_test;

typedef struct s_perm
{
	pthread_mutex_t	mutex_access;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_time;
	t_bool			stop;
}					t_perm;

typedef struct s_simu
{
	struct timeval	time_start;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				end_if;
}					t_simu;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_philo
{
	int				num;
	int				nb_eat;
	t_state			state;
	t_state			mem_state;
	t_state			state_bf_die;
	pthread_mutex_t	his_fork;
	pthread_mutex_t	*neighbour_fork;
	unsigned long	last_eat;
	unsigned long	start_eat;
	pthread_t		thread;
	t_simu			simu;
	t_perm			*perm;
}					t_philo;

int					ft_atoi(char *nptr);

t_philo				*init(t_philo *philo, t_perm *perm_main, int ac, char **av);

int					cmp_state(char *state, char *test_state);
t_philo				*print_state(t_philo *philo);
unsigned long		get_pgrm_time(struct timeval start);
void				*ft_thread(void *arg);
void				create_thread(t_philo *philo);

int					print_not_enought_arg_error(int ac);

#endif