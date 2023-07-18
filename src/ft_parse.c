/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:25:19 by msamhaou          #+#    #+#             */
/*   Updated: 2023/07/18 10:01:15 by msamhaou         ###   ########.fr       */
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
		height++;
		if (!line)
			break;
		if (!ft_valid((const char *)line))
			return (free(line), exit(1), NULL);
		width = ft_max(width, ft_strlen(line));
		// free(line);
	}
	// if (tmp)
	// 	free(tmp);
	dimension[0] = width;
	dimension[1] = height;
	return (dimension);
}

int	ft_map_component_find(char c)
{
	if (c == '1')
		return (1);
	if (c == 'N')
		return (8);
	if (c == ' ' || c == '\n')
		return (2);
	return (0);
}

int	*ft_map_fill(int fd, int width, int height)
{
	char	*line;
	int		i;
	int		*map;
	int		j, k ;

	map = malloc(sizeof(int) * (width * height));
	printf("H : %d\n", height);
	printf("W : %d\n", width);
	i = 0;
	j = 0;
	k = 0;
	while (k < height)
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
				map[k * width + j] = ft_map_component_find(*line);
			i++;
			j++;
			line++;
		}
		k++;
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

int	ft_strcmp(const char *s1, const char *s2)
{
	char	*ps1;
	char	*ps2;

	ps1 = (char *)s1;
	ps2 = (char *)s2;
	while (*ps1 || *ps2)
		if (*ps1 != *ps2)
			return (*ps1 - *ps2);
	return (0);
}

void	ft_get_xpm_files(t_data *data, int fd)
{
	char *line;
	t_file	*file;

	file = data->file;
	int	i;

	i = 0;
	while (i < 4)
	{
		line = get_next_line(fd);
		if (!ft_strncmp(line, "NO ", ft_strlen("NO ")))
			file->north = ft_substr(line, (unsigned int)ft_strlen("NO "), ft_strlen(line));
		else if (!ft_strncmp(line, "SO ", ft_strlen("SO ")))
			file->south = ft_substr(line, (unsigned int)ft_strlen("SO "), ft_strlen(line));
		else if (!ft_strncmp(line, "WE ", ft_strlen("WE ")))
			file->west = ft_substr(line, (unsigned int)ft_strlen("WE "), ft_strlen(line));
		else if (!ft_strncmp(line, "EA ", ft_strlen("EA ")))
			file->east = ft_substr(line, (unsigned int)ft_strlen("EA "), ft_strlen(line));
		free(line);
		i++;
	}
}
void	ft_free_strings(char **s)
{
	while (*s)
		free(*(s++));
	free(s);
}

int	ft_get_color(char *str, char *s)
{
	char	*raw;
	char	**split;
	int		res;

	raw = ft_substr(str, (unsigned int)ft_strlen(s), ft_strlen(str));
	printf("%s\n", raw);
	split = ft_split(raw, ',');
	res = color_code(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[3]));
	ft_free_strings(split);
	return (res);
}

void	ft_get_colors(t_data *data, int fd)
{
	int	i;
	char	*line;
	t_color	*color;

	color = data->colors;
	i = 0;
	while (i < 6)
	{
		line = get_next_line(fd);
		// printf("%s\n", line);
		// if (line[0] == '\n')
		// {
		// 	continue;
		// 	free(line);
		// }
		printf("%d\n", i);
		if (!ft_strncmp(line, "F ", ft_strlen("F ")))
			color->floor = ft_get_color(line, "F ");
		else if (!ft_strncmp(line, "C ", ft_strlen("C ")))
			color->floor = ft_get_color(line, "C ");
		// free(line);
		i++;
	}
	printf("HERE\n");
}

void	ft_parse(char *filename, t_data *data)
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
	ft_get_xpm_files(data, fd);
	ft_get_colors(data, fd);
	printf("%d\n", data->colors->ciel);
	dimensions = ft_get_dim(fd);
	close(fd);
	fd = open(filename, O_RDONLY);
	map = ft_map_fill(fd, dimensions[0], dimensions[1]);
	data->map->map_compo = map;
	data->map->xmap = dimensions[0];
	data->map->ymap = dimensions[1];
	ft_wall_check(dimensions, map);
}
