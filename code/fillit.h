/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:07:40 by parkharo          #+#    #+#             */
/*   Updated: 2022/01/11 18:41:23 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_block
{
	unsigned int	bitmap[4];
	int				x;
	int				y;
	int				width;
	int				height;
	struct s_block	*previous;
}				t_block;

typedef struct s_field
{
	unsigned int	*bitmap;
	int				size;
}				t_field;

int				validate_input(char *buf, int count, t_block ***result);

int				solve_fillit(t_field *f, t_block **input, int count, int i);

t_block			*create_block(void);
t_block			*match_block(t_block *block, t_block **arr, int index);
int				realign_block(t_block *block);
int				delete_block(t_block **block);
int				delete_block_arr(t_block **arr, int count);

int				set_bit(int bit, unsigned int number);
int				clear_bit(int bit, unsigned int number);
int				check_bit(int bit, unsigned int number);
unsigned short	popcountl(unsigned int number);
void			fill_popcount_table(void);

t_field			*init_field(int size);
int				get_square_size(int count);
void			free_field(t_field **field);

void			print_result(int size, t_block **arr, int count);

#endif
