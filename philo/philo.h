/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:57:11 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/26 19:45:08 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				num;
	struct timeval	time_start;
	char			*state;
	char			*mem_state;
	int				last_eat;
	pthread_t		thread;
}			t_philo;

typedef struct s_simu
{
	t_philo			*philo;
	struct timeval	time_start;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				end_if;
}			t_simu;

int				ft_atoi(char *nptr);

void			init(t_simu *simu, int ac, char **av);

void			print_state(t_simu simu);

unsigned long	get_pgrm_time(struct timeval start);

#endif