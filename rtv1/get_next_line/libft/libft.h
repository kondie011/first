/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 12:12:48 by knedzing          #+#    #+#             */
/*   Updated: 2018/09/14 13:49:46 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# define ABS(x) (x < 0 ? -x : x)
# define PI 3.1415926
# define DEG2RAD PI / 180
# define RAD2DEG 180 / PI

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;
typedef struct		s_vec3
{
	double	x;
	double	y;
	double	z;
}					t_vec3;
t_vec3				vec3_zero(void);
t_vec3				vec3_up(void);
t_vec3				vec3_right(void);
t_vec3				vec3_forward(void);
t_vec3				vec3(double x, double y, double z);
t_vec3				vec3_add(t_vec3 va, t_vec3 vb);
t_vec3				vec3_sub(t_vec3 va, t_vec3 vb);
t_vec3				vec3_mul(t_vec3 va, t_vec3 vb);
t_vec3				vec3_fmul(t_vec3 v, double m);
double				vec3_dot(t_vec3 va, t_vec3 vb);
void				vec3_rot(t_vec3 *v, int axis, double theta);
void				vec3_clamp(t_vec3 *v, double min, double max);
t_vec3				vec3_cross(t_vec3 va, t_vec3 vb);
t_vec3				vec3_norm(t_vec3 v);
t_vec3				vec3_reflect(t_vec3 v, t_vec3 n);
t_vec3				vec3_scale(t_vec3 va, double scale);
double				vec3_magnitude(t_vec3 v);
void				vec3_normalize(t_vec3 *v);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *s1, const void *s2, size_t n);
void				*ft_memccpy(void *s1, const void *s2, int c, size_t n);
void				*ft_memmove(void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *s1, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *s1, const char *s2, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(const char *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(const char *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
double				ft_atof(const char *str);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_vec3				ft_htoc(int hex);
int					ft_atoi_base(char *str, int base);

#endif
