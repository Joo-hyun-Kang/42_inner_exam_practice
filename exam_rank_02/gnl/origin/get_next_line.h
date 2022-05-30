/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jokang <autoba9687@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:13:40 by jokang            #+#    #+#             */
/*   Updated: 2022/05/30 23:41:08 by jokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

# define TRUE (1)
# define FALSE (0)

# define BUFFER_SIZE (10)

typedef struct s_table
{
	char	*string_pa;
	size_t	capacity;
	void	*next;
}	t_table;

typedef struct s_queue
{
	char	*buffer_pa;
	int		is_EOF;
	size_t	num_count;
	size_t	last_count;
}	t_queue;

enum { e_SIZE = 2048 };

int		build_queue_malloc(t_queue **queue);
void	free_t_struct(t_queue **queue, t_table **lst);
int		try_enqueue_fd(t_queue *queue_pa, int fd);
int		dequeue_by_next_line(t_queue *queue_pa, t_table *head);
char	*get_next_line(int fd);

void	*ft_memcpy(void *dst, const void *src, size_t n);
int		add_back_table_malloc(t_table **head);
t_table	*build_table_malloc(void);
int		is_table_capacity_full(t_table *table);
char	*ft_strdup_table_malloc(t_table *head);

#endif /* GET_NEXT_LINE_H */
