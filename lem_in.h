#ifndef LEM_IN_H
    #define LEM_IN_H

# include "./Libft/libft.h"
# include <stdio.h> //debug

typedef struct s_table
{
    int     rows;
    int     colums;
    char    *array;
}   t_table;

typedef struct s_path
{
    size_t          len;
    unsigned short	*nodes;
	unsigned short	group; 
}   t_path;

typedef struct s_data
{
    unsigned short	ants;
    unsigned short	p_start;
    unsigned short	p_end;
    char            *names;
	size_t			name_len;
	t_table			*t_adjacency;
    size_t          table_size;
    t_path          *paths;
    unsigned short	n_paths; //max paths
}   t_data;

//parser
void	file_parser(t_data *data);
int		is_int(char *str);
int		is_room(char *str);
int		is_link(char *str);

//table_2d
t_table *init_table(int rows, int colums, char value);
void    set_value(t_table *table, int row, int colum, char value);
char    get_value(t_table *table, int row, int colum);
void    print_table(t_table *table);
void    free_table(t_table *table);

#endif
