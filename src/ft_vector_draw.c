/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:24:33 by msamhaou          #+#    #+#             */
/*   Updated: 2023/07/04 19:15:03 by taha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	*ft_hypo_calc(t_vertex *a, t_vertex *b)
{
	float	*hypo;
	float	x;
	float	y;
	float	deg;

	x = (b->x - a->x);
	y = (a->y - b->y);
	hypo = malloc(sizeof(float) * 2);
	hypo[0] = sqrt(pow(x, 2) + pow(y, 2));
	hypo[1] = asin(y / hypo[0]);
	return (hypo);
}

void	ft_swap_vect(t_vertex **a, t_vertex **b)
{
	t_vertex	**tmp;

	tmp = a;
	*a = *b;
	*b = *tmp;
}

void	ft_vect_draw(t_vertex *a, t_vertex *b, int color, t_data *data)
{
	float	i;
	float	*hypo;
	float	*hypo_max;
	float	deg;
	float	adj;
	float	x;
	float	y;

	i = 0;
	hypo = ft_hypo_calc(a, b);

	x = 0;
	y = 0;
	while (i < hypo[0])
	{
		if ((int)a->x + x > 0 && (int)a->x + x < data->map->xmap * data->map->off_map &&  (int)a->y - y > 0 && (int)a->y - y < HEIGHT)
			ft_put_pix((int)a->x + x, (int)a->y - y, color, data);
		if (b->x < a->x)
			x -= cos(hypo[1]);
		else
			x+= cos(hypo[1]);
		y += sin(hypo[1]);

		i++;
	}
}
