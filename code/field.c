/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 15:30:29 by parkharo          #+#    #+#             */
/*   Updated: 2022/01/07 08:31:54 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * Usage:
 *
 * Initializes new t_field of minimal size required to accomodate count
 * amount of blocks
 * Field is initialized with square bitmap array set to 0 according to 
 * get_square_size function.
 */
t_field	*init_field(int size)
{
	int		bitmask;
	t_field	*field;

	field = (t_field *) malloc(sizeof(t_field));
	field->size = size;
	field->bitmap = (unsigned int *) malloc(sizeof(unsigned int) * size);
	bitmask = set_bit((sizeof(unsigned int) * 8) + size - 1, 0) - 1;
	while (size)
		field->bitmap[--size] = bitmask;
	return (field);
}

/*
 * Usage: 
 * Calculates the minimal square needed to accomodate count amount of blocks.
 * Each block consists of 4 elements, so count * 4 will be the minimum amount
 * of positions on map needed.
 * Field has to be a square, so square of the first number to be greater than 
 * count * 4 would be starting size of the field.
 */
int	get_square_size(int count)
{
	int	size;

	size = 2;
	while (size * size < count * 4)
		++size;
	return (size);
}

/* Usage:
 * 
 * Frees field's bitmap and the field itself.
 * 
 */
void	free_field(t_field **field)
{
	free((*field)->bitmap);
	free(*field);
}
