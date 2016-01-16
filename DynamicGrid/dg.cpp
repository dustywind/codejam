
#include <array>
#include <cassert>
#include <vector>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grid.h"

static inline std::vector<std::vector<int> *> *prepare_matrix(unsigned int, unsigned int);
static char *read_line(void);
static inline void clear_matrix(std::vector<std::vector<int> *> *);
static bool str_contains(const char *, char);

static void execute_case(int);
static Grid *prepare_grid();

int main(int argc, char *argv[])
{
    char *line = NULL;
    line = read_line();
    int number_of_cases = 0;
    sscanf(line, "%d\n", &number_of_cases);
    free(line);

    for(int c = 1; c <= number_of_cases; ++c)
    {
        execute_case(c);
    }

    return 0;
}


void execute_case(int case_nr)
{
    const int command_index = 0;

    printf("Case #%d:\n", case_nr);
    
    Grid *g = prepare_grid();

    char *line = read_line();
    int number_of_orders = 0;
    sscanf(line, "%d\n", &number_of_orders);
    free(line);


    for(int o = 0; o < number_of_orders; ++o)
    {
        line = read_line();
        switch(line[command_index])
        {
            case 'Q':
                printf("%d\n", g->q());
                break;
            case 'M':
                int row = 0, column = 0, value = 0;
                sscanf(line, "M %d %d %d", &row, &column, &value);

                g->m(row, column, value);
                break;
        }
        free(line);
    }
    delete g;
}

Grid *prepare_grid(void)
{
    int rows = 0, columns = 0;
    char *line = read_line();
    sscanf(line, "%d %d", &rows, &columns);
    free(line);

    std::vector<std::vector<int> *> *matrix = prepare_matrix(rows, columns);
    Grid *g = new Grid(rows, columns, matrix);
    clear_matrix(matrix);

    for(int r = 0; r < rows; ++r)
    {
        char *row = read_line();
        for(int c = 0; c < columns; ++c)
        {
            g->m(r, c, row[c] == '1');
        }
        free(row);
    }
    return g;
}


bool str_contains(const char *str, char findMe)
{
    char *tmp = (char *) str;
    while(*tmp)
    {
        if(*tmp == findMe)
        {
            return true;
        }
        tmp++;
    }

    return false;
}



char * read_line(void)
{
    char *line = NULL;
    char *error_code = NULL;
    const size_t default_size = 3;
    const size_t grow_by = 2;
    assert(grow_by > 1);
    size_t current_size = default_size;
    int current_begin = 0;

    line = (char *) malloc(current_size * sizeof(char));
    memset((void *)line, '\0', current_size);

    bool found_new_line_char = false;
    while(!found_new_line_char)
    {
        if(!fgets(&line[current_begin], current_size - current_begin, stdin))
        {
            return error_code;
        }

        found_new_line_char = str_contains(&line[current_begin], '\n');
        if(found_new_line_char)
        {
            break;
        }

        int new_size = current_size + grow_by;

        if(!(line = (char *)realloc((void *) line, new_size * sizeof(char))))
        {
            return error_code;
        }

        current_begin = current_size -1;
        memset(&line[current_begin], '\0', grow_by);

        current_size = new_size;
    }
    return line;
}




inline std::vector<std::vector<int> *> *prepare_matrix(unsigned int rows, unsigned int columns)
{
    const int initial_matrix_value = 0;
    std::vector<std::vector<int> *> *matrix = new std::vector<std::vector<int> *>;

    for(unsigned int r = 0; r < rows; ++r)
    {
        std::vector<int> *row = new std::vector<int>;
        matrix->push_back(row);
        for(unsigned int c = 0; c < columns; ++c)
        {
            row->push_back(initial_matrix_value);
        }
    }
    return matrix;
}

inline void clear_matrix(std::vector<std::vector<int> *> *matrix)
{
    for(unsigned int i = 0; i < matrix->size(); ++i)
    {
        auto row = (*matrix)[i];
        delete row;
    }
    delete matrix;
}


