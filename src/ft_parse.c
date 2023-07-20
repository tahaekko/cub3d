/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:25:19 by msamhaou          #+#    #+#             */
/*   Updated: 2023/07/19 08:52:38 by taha             ###   ########.fr       */
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
		while (line[0] != '1')
		{
			line = get_next_line(fd);
		}
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
				printf("here1\n");
				ft_putendl_fd("Fucked", 2);
				printf("%d\n", i * dim[0] + j);
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
				printf("here2\n");
				ft_putendl_fd("Fucked", 2);
				printf("%d\n", i * dim[0] + j);
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

	data->files_arr = malloc(sizeof(char *) * (5));
	int	i;

	i = 0;
	while (i < 4)
	{
		line = get_next_line(fd);
		if (!ft_strncmp(line, "NO ", ft_strlen("NO ")))
			data->files_arr[0] = ft_substr(line, (unsigned int)ft_strlen("NO "), ft_strlen(line) - ft_strlen("NO ") - 1);
		else if (!ft_strncmp(line, "SO ", ft_strlen("SO ")))
			data->files_arr[1] = ft_substr(line, (unsigned int)ft_strlen("SO "), ft_strlen(line) - ft_strlen("NO ") - 1);
		else if (!ft_strncmp(line, "WE ", ft_strlen("WE ")))
			data->files_arr[2] = ft_substr(line, (unsigned int)ft_strlen("WE "), ft_strlen(line) - ft_strlen("NO ") - 1);
		else if (!ft_strncmp(line, "EA ", ft_strlen("EA ")))
			data->files_arr[3] = ft_substr(line, (unsigned int)ft_strlen("EA "), ft_strlen(line) - ft_strlen("NO ") - 1);
		free(line);
		i++;
	}
	data->files_arr[i] = NULL;
}
void	ft_free_strings(char **s)
{
	while (*s)
		free(*(s++));
}

int	ft_set_color(char *str, char *s)
{
	char	*raw;
	char	**split;
	int		res;

	raw = ft_substr(str, (unsigned int)ft_strlen(s), ft_strlen(str));
	split = ft_split(raw, ',');
	res = color_code(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]));
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
	while (i < 2)
	{
		line = get_next_line(fd);
		if (line[0] == '\n')
		{
			continue;
			free(line);
		}
		if (!ft_strncmp(line, "F ", ft_strlen("F ")))
			color->floor = ft_set_color(line, "F ");
		else if (!ft_strncmp(line, "C ", ft_strlen("C ")))
			color->ciel=  ft_set_color(line, "C ");
		free(line);
		i++;
	}
	line = get_next_line(fd);
	free(line);
}

void	ft_xpm_file_check(t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	while (data->files_arr[i])
	{
		printf("%s\n", data->files_arr[i]);
		fd = open(data->files_arr[i], O_RDONLY);
		if (fd < 0){
			perror("");
			exit(1);
		}
		close(fd);
		i++;
	}
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
	ft_xpm_file_check(data);
	ft_get_colors(data, fd);
	printf("%d\n", data->colors->ciel);
	dimensions = ft_get_dim(fd);
	close(fd);
	fd = open(filename, O_RDONLY);
	map = ft_map_fill(fd, dimensions[0], dimensions[1]);
	for (int i = 0; i < dimensions[1]; i++)
	{
		for (int j = 0; j < dimensions[0]; j++)
			printf("%d", map[i * dimensions[0] + j]);
		printf("\n");
	}
	data->map->map_compo = map;
	data->map->xmap = dimensions[0];
	data->map->ymap = dimensions[1];
	ft_wall_check(dimensions, map);
}
