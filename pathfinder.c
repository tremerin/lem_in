#include "lem_in.h"


void order_paths(unsigned short num_paths, t_path *paths)
{
    size_t i = 0;
    size_t j = 0;
    size_t minor;
    t_path temp;
    size_t index = 0;
    while (i < num_paths)
    {
        j = i;
        minor = paths[i].len;
        index = j;
        while (j < num_paths)
        {
            if (paths[j].len < minor)
            {
                minor = paths[j].len;
                index = j;
            }
            j++;
        }
        temp = paths[i];
        paths[i] = paths[index];
        paths[index] = temp;
        i++;
    }
}


void init_queue(t_queue *queue, t_data *data)
{
    queue->data = malloc(sizeof(unsigned short) * data->table_size);
    queue->size = 0;
    queue->capacity = data->table_size;
    queue->front = 0;
    queue->rear = -1;
}


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


void queue_in(unsigned short element, t_queue *queue)
{
    if (queue->size < queue->capacity)
    {
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->data[queue->rear] = element;
        queue->size++;
    }
}


int bfs_shortest(t_data * data, t_table *residual, unsigned short *parent, unsigned short *distance)
{
    unsigned short *visited = malloc(sizeof(unsigned short) * data->table_size);
    ft_bzero(visited, sizeof(unsigned short) * data->table_size);
    t_queue queue; //queue

    init_queue(&queue, data);

    unsigned short start = data->p_start; //cojo start
    queue_in(start, &queue); //añadir start en queue
    visited[start] = 1; //lo pongo como visitado
    parent[start] = -1; //pongo en padre -1
    distance[start] = 0;

    int found_path = 0;

    while (queue.size > 0 && found_path == 0) //mientras queue tenga tamaño y no haya encontrado camino
    {
        unsigned short u = queue_out(&queue); //saco elemento de queue

        for (unsigned short v = 0; v < data->table_size; v++) //for por todos los elementos de table
        {
            int residual_capacity = get_value(residual, u, v);
            if (visited[v] == 0 && residual_capacity != 0) //compruebo si han sido visitados y si residual es 0
            {
                queue_in(v, &queue); //lo meto en la cola
                visited[v] = 1; //lo marco como visitado
                parent[v] = u; //pongo el padre
                if (residual_capacity > 0)
                {
                    distance[v] = distance[u] + 1;
                }
                else
                {
                    distance[v] = distance[u] - 1;
                }

                if (v == data->p_end) //si es end, paro while
                {
                    found_path = 1;
                    break;
                }
            }
        }
    }

    if (visited != NULL)
        free(visited);
    if (queue.data != NULL)
        free(queue.data);
    return found_path;
}


t_path extract_path_from_parent(t_data *data, unsigned short *parent, unsigned short *distance)
{
    t_path path;
    
    //contar longitud del camino
    int length = 0;
    unsigned short current = data->p_end;
    while (current != data->p_start) {
        length++;
        current = parent[current];
    }
    
    //crear array de nodos
    path.nodes = malloc(length * sizeof(unsigned short));
    path.len = length;
    path.cost = distance[data->p_end];
    
    //llenar array desde el final hacia atrás
    current = data->p_end;
    for (int i = length - 1; i >= 0; i--) {
        path.nodes[i] = current;
        current = parent[current];
    }
    
    return path;
}


void suurballe_tarjan(t_data *data, int max_paths)
{
    data->paths.paths = malloc(max_paths * sizeof(t_path));
    data->paths.num_paths = 0;
    data->paths.total_cost = 0;
    
    data->residual = copy_table(data->t_adjacency);

    unsigned short *parent = malloc(sizeof(unsigned short) * data->table_size);
    unsigned short *distance = malloc(sizeof(unsigned short) * data->table_size);
    ft_bzero(distance, sizeof(unsigned short) * data->table_size);
    
    for (int k = 0; k < max_paths; k++) {
        if (!bfs_shortest(data, data->residual, parent, distance)) {
            break; //no hay más caminos
        }
        
        //si el camino tiene costo no positivo después del primero, parar
        if (distance[data->p_end] <= 0 && k > 0) {
            break;
        }
        
        //extraer camino
        data->paths.paths[data->paths.num_paths] = extract_path_from_parent(data, parent, distance);
        data->paths.total_cost += data->paths.paths[data->paths.num_paths].cost;
        data->paths.num_paths++;
        
        //actualizar tabla residual
        for (unsigned short v = data->p_end; v != data->p_start; v = parent[v])
        {
            unsigned short u = parent[v];

            char current = get_value(data->residual, u, v);
            if (current > 0)
            {
                set_value(data->residual, u, v, 0);
                set_value(data->residual, v, u, -1);
            }
            else
            {
                set_value(data->residual, u, v, current - 1);
            }
        }
    }

    free(parent);
    free(distance);
}


int bfs(t_data * data, t_table *residual, unsigned short *parent)
{
    unsigned short *visited = malloc(sizeof(unsigned short) * data->table_size);
    ft_bzero(visited, sizeof(unsigned short) * data->table_size);
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

    if (visited != NULL)
        free(visited);
    if (queue.data != NULL)
        free(queue.data);
    return found_path;
}


int ford_fulkerson(t_data *data)
{
    data->ff_flow = init_table(data->t_adjacency->columns, data->t_adjacency->rows, 0);
    data->ff_residual = copy_table(data->t_adjacency);

    unsigned short *parent = malloc(sizeof(unsigned short) * data->table_size); //padres de cada nodo
    int max_flow = 0; //numero de hormigas que pueden pasar en un turno

    while (bfs(data, data->ff_residual, parent) == 1)
    {
        int path_flow = INT_MAX;
        
        //capacidad mínima del camino, cuantas hormigas pueden pasar a la vez
        for (unsigned short v = data->p_end; v != data->p_start; v = parent[v])
        {
            unsigned short u = parent[v];
            int r_capacity = get_value(data->ff_residual, u, v);
            if (r_capacity < path_flow)
            {
                path_flow = r_capacity;
            }
        }

        //actualizar los flujos directos y reversos
        for (unsigned short v = data->p_end; v != data->p_start; v = parent[v])
        {
            unsigned short u = parent[v];
            char current = get_value(data->ff_flow, u, v);
            set_value(data->ff_flow, u, v, current + path_flow);

            char reverse = get_value(data->ff_flow, v, u);
            set_value(data->ff_flow, v, u, reverse - path_flow);

            char current_residual = get_value(data->ff_residual, u, v);
            set_value(data->ff_residual, u, v, current_residual - path_flow);
            
            char reverse_residual = get_value(data->ff_residual, v, u);
            set_value(data->ff_residual, v, u, reverse_residual + path_flow);
        }

        max_flow += path_flow;
    }

    free(parent);
    return max_flow;
}


void disjunt_paths(t_data *data, int max_flow)
{
    t_table *flow_table = copy_table(data->ff_flow);
    
    data->ff_paths.n_paths = max_flow;
    data->ff_paths.paths = malloc(sizeof(t_path) * data->ff_paths.n_paths);
    
    for (int i = 0; i < max_flow; i++)
    {
        unsigned short current = data->p_start;
        data->ff_paths.paths[i].len = 0;
        data->ff_paths.paths[i].nodes = malloc(sizeof(unsigned int) * data->table_size);
        data->ff_paths.paths[i].nodes[0] = current;
        
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
            data->ff_paths.paths[i].nodes[data->ff_paths.paths[i].len] = current;
            data->ff_paths.paths[i].len++;
        }
        
    }
    free_table(flow_table);
}


void find_paths(t_data *data)
{
    if (data->table_size < 1500)
    {
        int max_flow = ford_fulkerson(data);
        if (max_flow)
        {
            disjunt_paths(data, max_flow);
        }
        else
        {
            printf("No hay camino posible\n");
            exit(EXIT_FAILURE);
        }
    }
    suurballe_tarjan(data, 15);
    if (data->paths.num_paths == 0)
    {
        printf("No hay camino posible\n");
        exit(EXIT_FAILURE);
    }
}
