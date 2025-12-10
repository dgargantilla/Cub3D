/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dediaz-f <dediaz-f@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:30:40 by dediaz-f          #+#    #+#             */
/*   Updated: 2024/03/09 16:30:40 by dediaz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdint.h>

int		ft_isalnum(int c);

int		ft_isalpha(int c);

int		ft_isascii(int c);

int		ft_isdigit(int c);

int		ft_isprint(int c);

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t count, size_t n);

void	*ft_memchr(void const *str, int c, size_t n);

int		ft_memcmp(void const *s1, void const *s2, size_t n);

void	*ft_memcpy(void	*dest, void const *src, size_t n);

void	*ft_memmove(void *dest, const void *src, size_t n);

void	*ft_memset(void *str, int c, size_t n);

void	ft_putchar_fd(char c, int fd);

void	ft_putendl_fd(char *s, int fd);

void	ft_putnbr_fd(int n, int fd);

void	ft_putstr_fd(char *s, int fd);

long	ft_atoi(char const *nptr);

char	*ft_itoa(int n);

char	**ft_split(char const *s, char c);

char	*ft_strchr(char const *str, int c);

char	*ft_strdup(char const *src);

void	ft_striteri(char *s, void (*f)(unsigned int, char *));

char	*ft_strjoin(char const *s1, char const *s2);

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

size_t	ft_strlcpy(char *dest, char const *src, size_t n);

size_t	ft_strlen(char const *str);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int		ft_strncmp(char const *s1, char const *s2, size_t n);

char	*ft_strnstr(char const *haystack, char const *needle, size_t n);

char	*ft_strrchr(char const *str, int c);

char	*ft_strtrim(char const *s1, char const *set);

char	*ft_substr(char const *s, unsigned int start, size_t len);

int		ft_tolower(int c);

int		ft_toupper(int c);

#endif
