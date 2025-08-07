#ifndef LEM_IN_H
    #define LEM_IN_H

# include "./Libft/libft.h"
# include <stdio.h> //debug

typedef struct s_path
{
    size_t          len;
    unsigned short	*nodes;
    unsigned short  valid; 
}   t_path;

typedef struct s_table
{
    unsigned int    rows;
    unsigned int    colums;
    char            *array;
}   t_table;

typedef struct s_multi_str
{
    char            *array;
    size_t          count;
    size_t          len_str;
    size_t          max_str;
}	t_multi_str;

typedef struct s_data
{
    unsigned short	ants;
    unsigned short	p_start;
    unsigned short	p_end;
    t_multi_str     *names;
	t_table			*t_adjacency;
    t_table         *t_weights;
    size_t          table_size;
    size_t          max_forks;
    short int       *dist_start;
    short int       *dist_end;
    short int       *multiplier;
    size_t          valid_paths;
    size_t          n_paths;
    t_path          *paths;
    unsigned short  **groups;
}   t_data;

//parser
void	    file_parser(t_data *data);
int		    is_int(char *str);
int		    is_room(char *str);
int		    is_link(char *str);

//node_distance
void        init_distances(t_data *data);
void        assign_distance(t_table *table, short int *distances, unsigned short p_init, unsigned short p_end);
void        print_distances(t_data *data);
void        weight_table(t_data *data);
void        assing_multiplier(t_data *data);
void        print_multipliers(t_data data);

//pathfinder
void        number_of_paths(t_data *data);
void        path_finding(t_data *data);
void        print_paths(t_data *data, unsigned int paths);
int         contain_pos(unsigned short *positions, unsigned int pos, size_t len);

//group paths
void        group_paths(t_data *data, unsigned int paths);

//ants movement
size_t      num_lines(unsigned short ants, size_t *paths_len, size_t n_paths);

//multi string
t_multi_str *init_multi_str(size_t size, size_t len);
void        add_str(t_multi_str *multi, char *str);
char        *str_pos(t_multi_str *multi, size_t pos);
size_t      get_str_index(t_multi_str *multi, char *str);
void        free_multi_str(t_multi_str *multi);

//table_2d
t_table     *init_table(int rows, int colums, char value);
void        set_value(t_table *table, int row, int colum, char value);
char        get_value(t_table *table, int row, int colum);
void        print_table(t_table *table);
void        free_table(t_table *table);

#endif
