/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:57:11 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/22 13:17:44 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK "has taken a fork\n"
# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define DIE "is died\n"

typedef struct s_fork
{
	int				status;
	pthread_mutex_t	fork;
	pthread_mutex_t	access;
}					t_fork;

typedef struct s_simu
{
	pthread_mutex_t	mutex_access;
	int				stop;
	int				done_eating;
	pthread_mutex_t	mutex_print;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				end_if;
	long long		time_start;
}					t_simu;

typedef struct s_philo
{
	int				num;
	int				nb_eat;
	long long		last_eat;
	t_fork			his_fork;
	t_fork			*neighbour_fork;
	pthread_t		thread;
	t_simu			*simu;
}					t_philo;

int					print_not_enought_argerror(int ac);

int					ft_atoi(char *nptr);

t_philo				*init(t_philo *philo, t_simu *simu_main, int ac, char **av);

long long			get_pgrm_time(long long pgrm_start);

void				print_state(t_philo *philo, char *state);

int					create_thread(t_philo *philo, t_simu simu);

void				*ft_thread(void *arg);

int					test_fork(t_philo *philo);
int					is_end(t_philo *philo);
void				is_die(t_philo *philo);
void				reset_fork(t_philo *philo);

#endif