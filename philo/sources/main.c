/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:58:27 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/14 09:53:07 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_perm	perm_main;

	if (ac < 5 || ac > 6)
		exit(print_not_enought_arg_error(ac));
	philo = NULL;
	philo = init(philo, &perm_main, ac, av);
	create_thread(philo);
	pthread_mutex_destroy(&perm_main.mutex_print);
	pthread_mutex_destroy(&perm_main.mutex_access);
	pthread_mutex_destroy(&philo->perm->mutex_time);

	return (0);
}
