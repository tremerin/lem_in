#include "lem_in.h"


t_table *init_table(int rows, int columns, char value)
{
    t_table *new = malloc(sizeof(t_table));
    new->rows = rows;
    new->columns = columns;
    int size = rows * columns;
    new->array = malloc(sizeof(char) * size);
    if (!new->array)
    {
        perror("Error: no memory");
        free(new);
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (i < size)
    {
        new->array[i] = value;
        i++;
    }
    return new;
}


void    set_value(t_table *table, int row, int colum, char value)
{
    table->array[(table->columns * row) + colum] = value;
}


char    get_value(t_table *table, int row, int colum)
{
    return (table->array[(table->columns * row) + colum]);
}


void    free_table(t_table *table)
{
    free(table->array);
    free(table);
}


t_table *copy_table(t_table *copy)
{
    t_table *paste = init_table(copy->columns, copy->rows, 0);

    int size = copy->columns * copy->rows;
    int i = 0;
    while (i < size)
    {
        paste->array[i] = copy->array[i];
        i++;
    }
    return paste;
}