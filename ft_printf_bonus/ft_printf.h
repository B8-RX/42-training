/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:06:29 by ssghioua          #+#    #+#             */
/*   Updated: 2024/01/16 11:06:31 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_PRINTF_H
 #define FT_PRINTF_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>		

#define BASE_LOW "0123456789abcdef"
#define BASE_UP "0123456789ABCDEF"

typedef	struct s_flags {
	int		period;
	int		precision;
	int		blank;
	int		zero;
	int		hashtag;
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
	int		error;
}	t_printf;

int			ft_printf(char *format, ...);
t_printf	*ft_init_printf_props(t_printf *props);
void		ft_end_process(t_printf *printf_props);
int			ft_handle_percent(t_printf *printf_props, char *format);
t_printf	*ft_handle_format(t_printf **printf_props, char *format);
t_printf	*ft_check_special_flags(t_printf **printf_props, char *format);
char		*ft_infill_str(t_printf *printf_props, char *infill, char *str);
char		*ft_update_str(t_printf *printf_props, char *str);
char		*ft_handle_precision(t_printf *printf_props, char *str);
char		*ft_handle_plus(char *str, char *infill);
char		*ft_handle_minus(char *str, char *infill);
char		*ft_justify_right(t_printf *printf_props, char *str, char *infill);
char		*ft_justify_left(char *str, char *infill);
int			ft_print_str(t_printf *printf_props, char *str);
int			ft_print_char(t_printf **printf_props, char c);
int			ft_atoi(char *str);
int			ft_print_unsigned(unsigned int nb, int len);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlcpy(char *dst, char *src, size_t size);
size_t		ft_strlen(char *str);
char		*ft_itoa(t_printf *printf_props, int nb);
char		*ft_uitoa(unsigned int n);
char		*ft_ultoa(t_printf *printf_props, unsigned long n);
char		*ft_append_char_str(char *str, char c, int position);
void		ft_init_specifier(t_printf *printf_props, char format);
void		*ft_handle_error_format(t_printf *printf_props, char *format);

#endif // !FT_PRINTF_H
