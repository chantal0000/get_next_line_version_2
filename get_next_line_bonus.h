/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:15:37 by chbuerge          #+#    #+#             */
/*   Updated: 2023/06/28 11:41:45 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

/*malloc and free*/
# include <stdlib.h>
/*read*/
# include <unistd.h>

/*define the required constant BUFFER_SIZE */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# ifndef FD_MAX
#  define FD_MAX 1000
# endif

/*get_next_line*/
char	*ft_read(int fd, char *str);
char	*get_next_line(int fd);
/*get_next_line_utils*/
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
char	*ft_extract_line(char *stash);
char	*ft_remove_extracted_line_from_stash(char *stash);

#endif
