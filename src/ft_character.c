/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_character.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:25:04 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/25 02:20:23 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_rect	*ft_rect_init()
{
	t_rect *rect;

	rect = malloc(sizeof(t_rect));
	rect->height = 5;
	rect->width = 5;
	rect->xpos = 300;
	rect->ypos = 300;
	rect->ray_len = 200;
	rect->deg = 6.24;
	rect->color = RECTCOLOR;
	return(rect);
}

void	ft_draw_character(t_data *data)
{
	t_rect *rect = data->rect;
	for (int i = 0; i < rect->width;i++)
		for(int j = 0; j < rect->height; j++)
			ft_put_pix(rect->xpos + i, rect->ypos + j, rect->color, data);
}
