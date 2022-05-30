/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jokang <autoba9687@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:10:11 by jokang            #+#    #+#             */
/*   Updated: 2022/01/07 14:33:37 by jokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>

int	build_queue_malloc(t_queue **queue)
{
	if (*queue == NULL)
	{
		*queue = (t_queue *)malloc(sizeof(t_queue));
		(*queue)->buffer_pa = ((char *)malloc(sizeof(char) * BUFFER_SIZE));
		(*queue)->is_EOF = FALSE;
		(*queue)->num_count = 0;
		(*queue)->last_count = 0;
	}
	return (TRUE);
}

int	try_enqueue_fd(t_queue *queue_pa, int fd)
{
	int	ret;

	ret = read(fd, queue_pa->buffer_pa, BUFFER_SIZE);
	if (ret < 0)
		return (FALSE);
	if (ret == 0)
	{
		queue_pa->is_EOF = TRUE;
		queue_pa->num_count = 0;
		return (FALSE);
	}
	if (ret < BUFFER_SIZE)
	{
		queue_pa->num_count = ret;
		queue_pa->last_count = ret;
		queue_pa->is_EOF = TRUE;
	}
	else
		queue_pa->num_count = BUFFER_SIZE;
	return (TRUE);
}

int	dequeue_by_next_line(t_queue *queue_pa, t_table *head)
{
	char	*buffer;
	char	*string;

	while (head->next != NULL)
		head = head->next;
	string = head->string_pa + head->capacity;
	buffer = queue_pa->buffer_pa;
	if (queue_pa->is_EOF == TRUE)
		buffer += (queue_pa->last_count - queue_pa->num_count);
	else
		buffer += (BUFFER_SIZE - queue_pa->num_count);
	while (queue_pa->num_count != 0 && head->capacity != e_SIZE)
	{
		*string++ = *buffer++;
		queue_pa->num_count--;
		head->capacity++;
		if (*(string - 1) == '\n' \
				|| (queue_pa->is_EOF && queue_pa->num_count == 0))
		{
			return (TRUE);
		}
	}
	return (FALSE);
}

void	free_t_struct(t_queue **queue, t_table **lst)
{
	t_table	*p;

	if (queue != NULL && *queue != NULL)
	{
		free((*queue)->buffer_pa);
		free(*queue);
		*queue = NULL;
	}
	if (lst != NULL)
	{
		while (*lst != NULL)
		{
			free((*lst)->string_pa);
			p = (*lst)->next;
			free(*lst);
			*lst = p;
		}
	}
}

char	*get_next_line(int fd)
{
	static t_queue	*queue_pa = NULL;
	t_table			*head;
	char			*result;

	build_queue_malloc(&queue_pa);
	if (queue_pa->num_count == 0 && !try_enqueue_fd(queue_pa, fd))
	{
		free_t_struct(&queue_pa, NULL);
		return (NULL);
	}
	head = build_table_malloc();
	while (dequeue_by_next_line(queue_pa, head) == FALSE)
	{
		if (queue_pa->num_count == 0)
			if (try_enqueue_fd(queue_pa, fd) == FALSE)
				break ;
		if (is_table_capacity_full(head) == TRUE)
			add_back_table_malloc(&head);
	}
	result = ft_strdup_table_malloc(head);
	free_t_struct(NULL, &head);
	if (queue_pa->is_EOF && queue_pa->num_count == 0)
		free_t_struct(&queue_pa, NULL);
	return (result);
}
