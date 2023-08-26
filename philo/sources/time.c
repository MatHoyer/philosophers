/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:33:09 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/26 19:41:36 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long get_pgrm_time(struct timeval start)
{
	struct timeval curent;
	
	gettimeofday(&curent, NULL);
	return ((curent.tv_sec * 1000 + curent.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000));
}