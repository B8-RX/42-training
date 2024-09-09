/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 02:03:55 by ssghioua          #+#    #+#             */
/*   Updated: 2024/08/25 03:35:35 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFFER_SIZE 10
# define BASE_LOW "0123456789abcdef"
# define BASE_UP "0123456789ABCDEF"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <fcntl.h> 

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

typedef struct s_flags {
	int		period;
	int		precision;
	int		blank;
	int		zero;
	int		sharp;
	int		plus;
	int		minus;
	int		width;
}	t_flags;

typedef struct s_printf {
	va_list	args;
	t_flags	*flags;
	char	specifier;
	int		flags_len;
	int		format_len;
	int		updated;
	char	*base;
	int		negative_nbr;
	int		error_format;
}	t_printf;

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_atoi(const char *nptr);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strtrim(const char *s1, const char *set);
char		*ft_strdup(const char *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_substr(const char *s, unsigned int start, size_t len);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

int			ft_tolower(int c);
int			ft_toupper(int c);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putendl_fd_nl(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_itoa(int n);
char		**ft_split(const char *s, char c);

char		*ft_update_stash(char *stash, char *buff, size_t size);
char		*ft_get_line(char *stash);
char		*ft_read_file(int fd, char *stash);
char		*get_next_line(int fd);

int			ft_printf(const char *format, ...);
t_printf	*ft_init_printf_props(t_printf *props);
int			ft_end_process(t_printf *printf_props, const char *format);
int			ft_verify_format(t_printf *printf_props, const char *format);
t_printf	*ft_verify_flags(t_printf *printf_props, const char *format, int i);
t_printf	*ft_format_processing(t_printf **printf_props, const char *format);
char		*ft_flags_processing(t_printf *printf_props, char *str);
t_printf	*ft_handle_flags(t_printf *printf_props, const char *format);
int			ft_handle_minus_flag(t_printf *printf_props, char prev_char);
int			ft_handle_plus_flag(t_printf *printf_props, char prev_char);
int			ft_handle_period_flag(t_printf *printf_props);
int			ft_handle_zero_flag(t_printf *printf_props,
				const char *format, int i);
int			ft_handle_num_flag(t_printf *printf_props,
				const char *format, int i);
int			ft_handle_sharp_flag(t_printf *printf_props,
				const char *format, int i);
void		*ft_handle_err_format(t_printf *printf_props,
				const char *format, int i);
void		ft_save_specifier_if_found(t_printf *printf_props,
				const char format);
void		ft_handle_s_specifier(t_printf *printf_props);
char		*ft_uitoa(unsigned int n);
char		*ft_ultoa(t_printf *printf_props, unsigned long n);
int			ft_atoi_printf(char *str);
char		*ft_itoa_printf(t_printf *printf_props, int nb);
int			ft_print_char(t_printf *printf_props, char c);
int			ft_handle_char_with_flags(t_printf *printf_props, char c);
void		*ft_print_percent_sign(t_printf *printf_props);
int			ft_print_str(t_printf *printf_props, char *str);
char		*ft_update_str(t_printf *printf_props, char *str);
char		*ft_slice_str(t_printf *printf_props, char *str);
char		*ft_set_infill(t_printf *props, char *str);
char		*ft_populate_infill(t_printf *printf_props,
				char *infill, char *str);
char		*ft_infill_precision(t_printf *props, char *str_input);
char		*ft_infill_width(t_printf *props, char *infill, int input_len);
char		*ft_justify_infill(t_printf *props, char *infill, char *str);
char		*ft_justify_infill_left(t_printf *printf_props,
				char *str, char *infill);
char		*ft_justify_infill_right(t_printf *printf_props,
				char *str, char *infill);
char		*ft_append_parity(t_printf *printf_props, char *str);
char		*ft_append_blank(t_printf *printf_props, char *src);
char		*ft_append_prefix_hexa(t_printf *printf_props, char *str);
char		*ft_append_char_to_str(char *str, char c, int c_position);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *str);
char		*ft_bzero_printf(int n);
#endif
