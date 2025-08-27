#include "lem_in.h"

size_t  next_node(t_data *data, int pos, size_t path, unsigned int *nexts)
{
    unsigned int    i = 0;
    size_t len = 0;
    while (i < data->table_size)
    {
        if (get_value(data->t_weights, pos, i) > 0 &&
            !contain_pos(data->paths[path].nodes, i, data->paths[path].len))
        {
            nexts[len] = i; 
            len += 1;
        }   
        i++;
    }
    return (len);
}

int contain_pos(unsigned short *positions, unsigned int pos, size_t len)
{
    size_t i = 0;
    while (i < len)
    {
        if (positions[i] == pos)
            return (1);
        i++;
    }
    return (0);
}

void    number_of_paths(t_data *data)
{
    unsigned int paths = 1;
    unsigned int checks;
    size_t      i = 0;
    while (i < data->table_size)
    {
        size_t  j = 0;
        checks = 0;
        while (j < data->table_size)
        {
            if (get_value(data->t_weights, i, j) == 1)
                checks++;
            j++;
        }
        if (checks > 1)
            paths += (checks * data->multiplier[i]);
        i++;
    }
    data->n_paths = paths;
    data->paths = malloc(sizeof(t_path) * data->n_paths);
    //calculate max path len
    i = 0;
    while (i < data->n_paths)
    {
        data->paths[i].len = 0;
        data->paths[i].nodes = malloc(sizeof(unsigned int) * data->table_size);
        i++;
    }
}

void    path_validation(t_data *data, unsigned int paths)
{
    size_t  i = 0;
    size_t  min_len = data->paths[0].len;
    size_t  average_len = 0;
    data->valid_paths = 0;
    while (i < paths)
    {
        if (data->paths[i].nodes[data->paths[i].len - 1] == data->p_end)
        {
            data->paths[i].valid = 1;
            //printf("%ld\n", data->paths[i].len); //print path len
            average_len += data->paths[i].len;
            data->valid_paths++;
            if (data->paths[i].len < min_len)
                min_len = data->paths[i].len;
        }
        else
            data->paths[i].valid = 0;
        i++;
    }
    printf("valid paths: %ld/%d\n", data->valid_paths, paths);
    printf("average len: %ld", average_len / data->valid_paths);
    //printf("min_len: %ld\n", min_len);
}

void    print_paths(t_data *data, unsigned int paths)
{
    size_t i = 0;
    while (i < paths)
    {
        size_t j = 0;
        if (data->paths[i].valid == 1)
        {
            printf("Path[%lu] ", i);
            while (j < data->paths[i].len)
            {
                printf("%s ", str_pos(data->names, data->paths[i].nodes[j]));
                j++;
            }
            printf("\n");
        }
        i++;
    }
}

void path_finding(t_data *data)
{
    //init paths
    data->paths[0].nodes[0] = data->p_start;
    data->paths[0].len = 1;
    //acutal number of paths
    unsigned int    paths = 1;
    //nexts nodes of pos
    unsigned int    *nexts = malloc(sizeof(unsigned int) * data->max_forks);
    size_t          nexts_len = 0;
    unsigned int    pos;

    //while any path is incomplete
    int incomplete = 1;
    size_t i = 0;
    size_t j = 0;
    while (incomplete)
    {
        i = 0;
        incomplete = 0;
        while (i < paths)
        {
            pos = data->paths[i].nodes[data->paths[i].len -1];
            //termina en la salida
            if (pos == data->p_end)
            {
                i++;
                continue;
            }
            nexts_len = next_node(data, pos, i, nexts);
            //termina sin salida
            if (nexts_len == 0)
            {
                //printf("no exit\n");
                i++;
                continue;
            }
            //continua el camino
            j = 0;
            while (j < nexts_len)
            {
                incomplete = 1;
                //añade otro nodo al camino actual
                if (j == 0)
                {
                    data->paths[i].nodes[data->paths[i].len] = nexts[j];
                    data->paths[i].len += 1;
                }
                //se bifurca
                else
                {
                    size_t cp = 0;
                    while (cp < data->paths[i].len)
                    {
                        data->paths[paths].nodes[cp] = data->paths[i].nodes[cp];
                        cp++;
                    }
                    data->paths[paths].nodes[cp -1] = nexts[j];
                    data->paths[paths].len = data->paths[i].len;
                    paths++;
                }
                j++;
            }
            i++;
        }
    }
    free(nexts);
    path_validation(data, paths);
    //print_paths(data, paths);
}

//init queue
void init_queue(t_queue *queue, t_data *data)
{
    queue->data = malloc(sizeof(unsigned short) * data->table_size);
    queue->size = 0;
    queue->capacity = data->table_size;
    queue->front = 0;
    queue->rear = -1;
}

//sacar elementos de queue
int queue_out(t_queue *queue)
{
    if (queue->size > 0)
    {
        unsigned short item = queue->data[queue->front];
        queue->front = (queue->front + 1) % queue->capacity;
        queue->size--;
        return item;
    }
    return -1;
}

//añadir elementos en queue
void queue_in(unsigned short element, t_queue *queue)
{
    if (queue->size < queue->capacity)
    {
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->data[queue->rear] = element;
        queue->size++;
    }
}

int bfs(t_data * data, t_table *residual, unsigned short *parent)
{
    unsigned short *visited = malloc(sizeof(unsigned short) * data->table_size);
    t_queue queue; //queue

    init_queue(&queue, data);

    unsigned short start = data->p_start; //cojo start
    queue_in(start, &queue); //añadir start en queue
    visited[start] = 1; //lo pongo como visitado
    parent[start] = -1; //pongo en padre -1

    int found_path = 0;

    while (queue.size > 0 && found_path == 0) //mientras queue tenga tamaño y no haya encontrado camino
    {
        unsigned short u = queue_out(&queue); //saco elemento de queue

        for (unsigned short v = 0; v < data->table_size; v++) //for por todos los elementos de table
        {
            if (visited[v] == 0 && get_value(residual, u, v) > 0) //compruebo si han sido visitados y si tienen residual
            {
                queue_in(v, &queue); //lo meto en la cola
                visited[v] = 1; //lo marco como visitado
                parent[v] = u; //pongo el padre

                if (v == data->p_end) //si es end, paro while
                {
                    found_path = 1;
                    break;
                }
            }
        }
    }
    return found_path;
}

int ford_fulkerson(t_data *data)
{
    data->flow = init_table(data->t_adjacency->columns, data->t_adjacency->rows, 0);
    data->residual = copy_table(data->t_adjacency);

    unsigned short *parent = malloc(sizeof(unsigned short) * data->table_size); //padres de cada nodo
    int max_flow = 0; //numero de hormigas que pueden pasar en un turno

    while (bfs(data, data->residual, parent))
    {
        int path_flow = INT_MAX;
        
        //capacidad mínima del camino, cuantas hormigas pueden pasar a la vez
        for (unsigned short v = data->p_end; v != data->p_start; v = parent[v])
        {
            unsigned short u = parent[v];
            int r_capacity = get_value(data->residual, u, v);
            if (r_capacity < path_flow)
            {
                path_flow = r_capacity;
            }
        }

        //actualizar los flujos directos y reversos
        for (unsigned short v = data->p_end; v != data->p_start; v = parent[v])
        {
            unsigned short u = parent[v];
            char current = get_value(data->flow, u, v);
            (void)current;
            //pasar current a int
            //set_value(flow, u, v, current + path_flow)
            set_value(data->flow, u, v, 1);

            char reverse = get_value(data->flow, v, u);
            (void)reverse;
            //pasar reverse a int
            //set_value(flow, v, u, current + path_flow)
            set_value(data->flow, v, u, -1);
        }

        max_flow += path_flow;
        //update residual
        int size = data->residual->columns * data->residual->rows;
        int i = 0;
        while (i < size)
        {
            char t_adj_val = data->t_adjacency->array[i];
            char flow_val = data->flow->array[i];
            char res_val = t_adj_val - flow_val;
            int row = i / data->residual->columns; //calculo la fila
            int column = i % data->residual->columns; //calculo la columna
            set_value(data->residual, row, column, res_val); 
            i++;
        }
    }

    return max_flow;
}


void disjunt_paths(t_data *data, int max_flow)
{
    t_table *flow_table = copy_table(data->flow);
    
    data->n_paths = max_flow;
    data->paths = malloc(sizeof(t_path) * data->n_paths);
    
    for (int i = 0; i < max_flow; i++)
    {
        unsigned short current = data->p_start;
        data->paths[i].len = 0;
        data->paths[i].nodes = malloc(sizeof(unsigned int) * data->table_size);
        data->paths[i].nodes[data->paths[i].len++] = current;
        
        while (current != data->p_end)
        {
            unsigned short next = -1;

            for (unsigned short v = 0; v < data->table_size; v++)
            {
                if (get_value(flow_table, current, v) > 0)
                {
                    next = v;
                    set_value(flow_table, current, v, 0);
                    break;
                }
            }

            if (next == (unsigned short)-1)
            {
                break; //no hay más flujo
            }

            current = next;
            data->paths[i].nodes[data->paths[i].len++] = current;
        }
        
    }
}


void find_paths(t_data *data)
{
    int max_flow = ford_fulkerson(data);

    if (max_flow)
    {
        //encontrar los caminos disjuntos
        printf("Número de caminos disjuntos: %d\n", max_flow);
        disjunt_paths(data, max_flow);
        for (size_t i = 0; i < data->n_paths; i++)
        {
            printf("Camino %li: ", i);
            for (size_t j = 0; j < data->paths[i].len; j++)
            {
                printf("%s ", str_pos(data->names, data->paths[i].nodes[j]));
            }
        }
    }
    else
    {
        //no encuentra camino
        printf("No hay camino posible\n");
    }
}