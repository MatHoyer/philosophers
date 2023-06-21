/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:57:11 by mhoyer            #+#    #+#             */
/*   Updated: 2023/06/21 13:39:59 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

typedef struct philo
{
	int		num;
	char	*state;
	char	*mem_state;
	int		last_eat;
}	t_philo;

typedef struct simu
{
	t_philo	*philo;
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		end_if;
}	t_simu;

# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

int		ft_atoi(char *nptr);

void	init(t_simu *simu, int ac, char **av);

void	print_state(t_simu simu);

#endif