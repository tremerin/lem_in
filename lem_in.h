#ifndef LEM_IN_H
    #define LEM_IN_H

# include "./Libft/libft.h"
# include <stdio.h> //debug
# include <limits.h> //INT_MAX
# include <stdio.h>

typedef struct s_queue
{
    unsigned short *data;
    int             size;
    int             capacity;
    int             front; //first element
    int             rear; //last element
}   t_queue; //cola circular

typedef struct s_path
{
    size_t          len;
    unsigned short	*nodes;
    unsigned short  valid;
    unsigned short  cost;
}   t_path;

typedef struct s_path_set
{
    size_t          num_paths;
    t_path          *paths;
    int             total_cost;
}   t_path_set;

typedef struct s_ff_path
{
    size_t          n_paths;
    t_path          *paths;
}   t_ff_path;

typedef struct s_table
{
    unsigned int    rows;
    unsigned int    columns;
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
    t_table         *residual;
    t_table         *ff_flow;
    t_table         *ff_residual;
    size_t          table_size;
    t_path_set      paths;
    t_ff_path       ff_paths;
    unsigned short  n_algo;
}   t_data;

//main
void            init_data(t_data *data);
void            free_data(t_data *data);
size_t          *paths_len(t_data *data);
size_t          *ff_paths_len(t_data *data);

//parser
int		        is_int(char *str);
int		        is_room(char *str);
int		        is_link(char *str);
char            *get_name(char *room);
void            read_link(t_data *data, char *link);
void	        file_parser(t_data *data);

//pathfinder
void            order_paths(unsigned short num_paths, t_path *paths);
void            init_queue(t_queue *queue, t_data *data);
int             queue_out(t_queue *queue);
void            queue_in(unsigned short element, t_queue *queue);
int             bfs_shortest(t_data * data, t_table *residual, unsigned short *parent, unsigned short *distance);
t_path          extract_path_from_parent(t_data *data, unsigned short *parent, unsigned short *distance);
void            suurballe_tarjan(t_data *data, int max_paths);
int             bfs(t_data * data, t_table *residual, unsigned short *parent);
int             ford_fulkerson(t_data *data);
void            disjunt_paths(t_data *data, int max_flow);
void            find_paths(t_data *data);

//ants movement
size_t          num_lines(unsigned short ants, size_t *paths_len, size_t n_paths);
unsigned short *assign_ants(unsigned short ants, size_t *paths_len, size_t n_paths);
unsigned short  first_ant(size_t path, unsigned short *ants);
void            moving_ants(t_data *data, size_t *paths_len, size_t n_paths, size_t lines);

//multi string
t_multi_str     *init_multi_str(size_t size, size_t len);
void            add_str(t_multi_str *multi, char *str);
void            add_room_name(t_multi_str *multi, char *str);
char            *str_pos(t_multi_str *multi, size_t pos);
size_t          get_str_index(t_multi_str *multi, char *str);
void            free_multi_str(t_multi_str *multi);

//table_2d
t_table         *init_table(int rows, int columns, char value);
void            set_value(t_table *table, int row, int colum, char value);
char            get_value(t_table *table, int row, int colum);
void            free_table(t_table *table);
t_table         *copy_table(t_table *copy);

#endif
