#include "lem_in.h"


t_table *init_table(int rows, int colums, char value)
{
    t_table *new = malloc(sizeof(t_table));
    new->rows = rows;
    new->colums = colums;
    int size = rows * colums;
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
    table->array[(table->colums * row) + colum] = value;
}

char    get_value(t_table *table, int row, int colum)
{
    return (table->array[(table->colums * row) + colum]);
}

void    print_table(t_table *table)
{
    if (table == NULL || table->rows == 0|| table->colums == 0)
    {
        printf("No data\n");
        return;
    }
    int i = 0;
    int size = table->rows * table->colums;
    while (i < size)
    {
        printf("%3d",table->array[i]);
        i++;
        if (i > 0 && i % table->colums == 0)
            printf("\n");
    }
}

void    free_table(t_table *table)
{
    free(table->array);
    free(table);
}
