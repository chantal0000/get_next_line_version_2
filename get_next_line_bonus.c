/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:08:25 by chbuerge          #+#    #+#             */
/*   Updated: 2023/06/28 11:31:48 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*BONUS:
Your get_next_line() can manage multiple 
file descriptors at the same time.
For example, if you can read from the 
file descriptors 3, 4 and 5, you should be
able to read from a different fd per 
call without losing the reading thread of each
file descriptor or returning a line from another fd.
It means that you should be able to call 
get_next_line() to read from fd 3, then
fd 4, then 5, then once again 3, 
once again 4, and so forth*/

#include "get_next_line_bonus.h"

static void	ft_join(char **stash, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(*stash, buffer);
	free(*stash);
	*stash = temp;
}

char	*ft_read(int fd, char *stash)
{
	char	*buffer;
	int		bytes_read_counter;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read_counter = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read_counter > 0)
	{
		buffer[bytes_read_counter] = '\0';
		if (!stash)
			stash = ft_strjoin("", buffer);
		else
			ft_join(&stash, buffer);
		if (ft_strchr(stash, '\n'))
			break ;
		bytes_read_counter = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes_read_counter == -1 && stash != 0)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[FD_MAX];
	char		*extracted_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = ft_read(fd, stash[fd]);
	if (!stash[fd] || !*stash[fd])
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	extracted_line = ft_extract_line(stash[fd]);
	stash[fd] = ft_remove_extracted_line_from_stash(stash[fd]);
	return (extracted_line);
}
/*
RETURN VALUE: Read line: correct behavior
NULL: there is nothing else to read, or an error
*/

/*test main function*/
/*
#include <stdio.h>
#include <fcntl.h>
int main(void)
{
	char	*temp;
	int	fd1, fd2, fd3;

	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	fd3 = open("test3.txt", O_RDONLY);
	// file 1
	temp = get_next_line(fd1);
	if (temp)
	{
	printf("file1: %s\n", temp);
	free(temp);
	}
	// file 2
	temp = get_next_line(fd2);
	if (temp)
	{
	printf("file2: %s\n", temp);
	free(temp);
	}
	// file 3
	temp = get_next_line(fd3);
	if (temp)
	{
	printf("file3: %s\n", temp);
	free(temp);
	}
	close(fd1);
    	close(fd2);
    	close(fd3);
	return (0);
}*/
