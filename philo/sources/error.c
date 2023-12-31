/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:50:49 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/22 11:52:35 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_not_enought_argerror(int ac)
{
	if (ac < 5)
	{
		printf("\033[31mError : ./philo needs at least 5 arguments.\033[0m\n");
		printf("\033[32mLike:\033[0m");
		printf(" ./philo number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep\n");
		printf("\033[32mAnd optional:\033[0m");
		printf(" number_of_times_each_philosopher_must_eat\n");
	}
	else
		printf("\033[31mError : too much arguments (%d).\033[0m\n", ac);
	return (1);
}
