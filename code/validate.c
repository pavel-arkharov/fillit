/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 13:06:03 by tpolonen          #+#    #+#             */
/*   Updated: 2022/01/11 18:17:48 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	validate_block(char *buf, t_block **arr, int i);
static int	validate_row(char *buf, t_block *block, int row);
static int	traverse_shape(int bitmap[4], t_point point);
static int	validate_shape(t_block *block);

/* Usage:
 * *buf is the buffer that contains the file that was read previously in
 * read_file. count is the amount of possible blocks.
 * ***result is the address where we will save the resulting array of blocks.
 *
 * Returns:
 * Amount of blocks that we found from the file, or -1 if there was an error.
 * 
 * Example:
 * char path[] = "sample.fillit"
 * char buf[600];
 * int count;
 * t_block **blocks;
 *
 * count = read_file(path, buf);
 * if (count == -1 || validate_input(buf, count, &blocks) == -1))
 * 	ft_putendl("error");
 */
int	validate_input(char *buf, int count, t_block ***result)
{
	t_block	**blocks;
	int		i;

	blocks = (t_block **) malloc(sizeof(t_block *) * count);
	i = 0;
	while (i < count)
	{
		if (i != count - 1)
			if (buf[((i + 1) * 21) - 1] != '\n')
				return (delete_block_arr(blocks, i));
		if (validate_block(buf, blocks, i) < 0)
			return (delete_block_arr(blocks, i));
		i++;
	}
	*result = blocks;
	return (count);
}

/*
 * Usage:
 * Validates that buffer contains a valid block in the given
 * position and adds it to the array provided by **arr parameter.
 *
 * Returns:
 * A positive value if a block was added to array successfully.
 * -1 if there was an error: block was not valid or allocation
 * failed.
 */
static int	validate_block(char *buf, t_block **arr, int i)
{
	t_block			*block;
	int				offset;
	int				row;
	unsigned int	width_check;

	block = (t_block *) ft_memalloc(sizeof(t_block));
	if (!block)
		return (-1);
	offset = i * 21;
	row = -1;
	while (++row < 4)
		if (validate_row(buf + offset + (row * 5), block, row) < 1)
			return (delete_block(&block));
	width_check = 0;
	while (row > 0)
		width_check |= block->bitmap[--row];
	block->width = popcountl(width_check);
	if (realign_block(block) == 1 && validate_shape(block) == 1)
	{
		block->previous = match_block(block, arr, i);
		arr[i] = block;
		return (1);
	}
	return (delete_block(&block));
}

/*
 * Usage:
 * Checks a row of input and assigns it to the t_block struct
 * that was provided as parameter. Makes sure that there are
 * no invalid characters, row lengths are correct and
 * newline is at expected position.
 *
 * Returns:
 * A positive value if row was validated correctly and it's
 * values were assigned to struct. 0 or -1 if there was an error:
 * Row data was invalid or assigning data to struct failed.
 */
static int	validate_row(char *buf, t_block *block, int row)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (buf[i] == '#')
			block->bitmap[row] = set_bit(i, block->bitmap[row]);
		else if (buf[i] != '.')
			return (0);
	}
	if (block->bitmap[row] != 0)
		block->height++;
	return (buf[i] == '\n');
}

/*
 * Usage:
 * Starting from a set bit on 4x4 bitmap, this functions traverses
 * recursively each cardinal direction (up, right, down, left in
 * this order) and counts all the set bits in that shape. Bits
 * are cleared after counting, so make a copy of the bitmap before
 * using this function!
 *
 * Returns:
 * Amount of set bits in a shape.
 */

static int	traverse_shape(int bitmap[4], t_point point)
{
	int		count;
	int		i;
	t_point	dirs[4];

	dirs[0] = (t_point){0, -1};
	dirs[1] = (t_point){1, 0};
	dirs[2] = (t_point){0, 1};
	dirs[3] = (t_point){-1, 0};
	count = 1;
	bitmap[point.y] = clear_bit(point.x, bitmap[point.y]);
	i = 0;
	while (i < 4)
	{
		dirs[i].x += point.x;
		dirs[i].y += point.y;
		if (dirs[i].x >= 0 && dirs[i].x <= 3
			&& dirs[i].y >= 0 && dirs[i].y <= 3)
		{
			if (check_bit(dirs[i].x, bitmap[dirs[i].y]))
				count += traverse_shape(bitmap, dirs[i]);
		}
		i++;
	}
	return (count);
}

/*
 * Usage:
 * Validates that block has a valid shape: all bits are connected
 * to each other cardinally, so only up/down or left/right connections
 * are permitted. Set bits are also counted, tetromino can only have
 * 4 bits set.
 *
 * Returns:
 * 1 if the shape is valid, -1 if there was an error:
 * shape was not connected properly or had more than 4 bits.
 */
static int	validate_shape(t_block *block)
{
	int		count;
	int		bitmap_copy[4];
	t_point	point;

	count = -1;
	while (++count < 4)
		bitmap_copy[count] = block->bitmap[count];
	point.y = 0;
	while (point.y < block->height)
	{
		point.x = 0;
		while (point.x < block->width)
		{
			if (check_bit(point.x, bitmap_copy[point.y]))
			{
				count -= traverse_shape(bitmap_copy, point);
				if (count != 0)
					return (-1);
			}
			point.x++;
		}
		point.y++;
	}
	return (1);
}
