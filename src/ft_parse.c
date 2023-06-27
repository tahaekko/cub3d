/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:25:19 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/27 18:01:20 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// N,S,E or W
int	ft_valid_c(char c)
{
	if (c != '0' || c!= '1' || c != 'N' \
			|| c != 'W' || c != 'S' || c != 'E')
		return (0);
	return (1);
}

int	ft_valid(const char *line)
{
	while (ft_valid_c(*line))
		if (!ft_valid_c(*(line++)))
			return (0);
	return (1);
}

int	ft_max(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}
int	*ft_get_dim(int fd)
{
	int		width;
	char	*line;
	char	*tmp;
	int		*dimension;
	int		height;

	line = get_next_line(fd);
	tmp = line;
	width = ft_strlen(line);
	height = 0;
	dimension = malloc(sizeof(int) * 2);
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (!ft_valid((const char *)line))
			return (free(line), exit(1), NULL);
		width = ft_max(width, ft_strlen(line));
		free(line);
		height++;
	}
	if (tmp)
		free(tmp);
	dimension[0] = width;
	dimension[1] = height;
	return (dimension);
}

int	ft_map_component_find(char c)
{
	if (c == '1')
		return (1);
	if (c == ' ' || c == '\n')
		return (2);
	return (0);
}

int	*ft_map_fill(int fd, int width, int height)
{
	char	*line;
	int		i;
	int		*map;
	int		j;

	map = malloc(sizeof(int) * (width * height));
	i = 0;
	j = 0;
	while (height)
	{
		line = get_next_line(fd);
		j = 0;
		while (j < width)
		{
			if (!(*line) && height)
			{
				map[i] = 2;
				*(line + 1) = '\0';
			}
			else
				map[i] = ft_map_component_find(*line);
			i++;
			j++;
			line++;
		}
		height--;
	}
	return (map);
}

void	ft_wall_check(int *dim, int * map)
{
	int	i;
	int	j;
	int	width;
	int	height;

	i = 0;
	j = 0;
	width = dim[0];
	height = dim[1];
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (i == 0 && map[i * dim[0] + j] == 0)
			{
				ft_putendl_fd("Fucked", 2);
				exit(1);
			}
			if ((map[i * dim[0] + j] == 0) &&
			(map[(i-1)* dim[0] + j] == 2 ||
			map[(i-1)* dim[0] + j - 1 ] == 2 ||
			map[(i-1)* dim[0] + j + 1 ] == 2 ||
			map[(i+1) *dim[0] + j] == 2 ||
			map[(i+1) *dim[0] + j - 1] == 2 ||
			map[(i+1) *dim[0] + j + 1] == 2 ||
			map[i * dim[0] + j + 1]== 2 ||
			map[i * dim[0] + j - 1] == 2))
			{
				ft_putendl_fd("Fucked", 2);
				exit(1);
			}
			j++;
		}
		i++;
	}
	ft_putendl_fd("Valid !", 1);
}

void	ft_parse(char *filename)
{
	int	fd;
	int	*dimensions;
	int	*map;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("");
		exit(1);
	}
	dimensions = ft_get_dim(fd);
	close(fd);
	fd = open(filename, O_RDONLY);
	map = ft_map_fill(fd, dimensions[0], dimensions[1]);
	ft_wall_check(dimensions, map);
	int i = 0;
	int j = 0;
	while (i < dimensions[1])
	{
		j = 0;
		while (j < dimensions[0])
			printf("%d", map[i * dimensions[0] + j++]);
		printf("\n");
		i++;
	}
}
