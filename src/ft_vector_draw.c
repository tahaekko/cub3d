/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:24:33 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/21 17:26:27 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_hypo_calc(t_vertex *a, t_vertex *b)
{
	double	hypo;
	double	x;
	double	y;

	x = b->x - a->x;
	y = b->y  - a->y;
	printf("x %f\n",x);
	printf("y %f\n", y);
	hypo = sqrt(pow(x, 2) + pow(y, 2));
	return (hypo);
}

void	ft_vect_draw(t_vertex *a, t_vertex *b, t_data *data)
{
	double	i;
	double	hypo;
	double	deg;

	i = 0;
	hypo = ft_hypo_calc(a, b);
	deg = acos((b->x - a->x) / hypo);
	printf("%f\n" , hypo);
	printf("%f\n" , deg);
	while (i < hypo)
	{
		ft_put_pix((int)(a->x + (i * cos(deg))), (int)(a->y + ( i * sin(deg))), 0x00FF00, data);
		i++;
	}
}
