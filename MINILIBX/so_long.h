#ifndef SO_LONG_H
# define SO_LONG_H
# define ERR_WALL "wall error\n"
 
typedef struct s_errors {
	char			*error_message;
	struct s_errors	*next;
} t_errors;

typedef struct s_map {
	char		*map_path;
	int			player;
	int			exit;
	int			empty;
	int			wall;
	char		*line;
	size_t		line_length;
	size_t		total_rows;
	int			collectibles;
	t_errors	*errors;
} t_map;

#endif
