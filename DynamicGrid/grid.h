
#ifndef __GRID_H_INCLUDED__
#define __GRID_H_INCLUDED__

#include <array>
#include <exception>
#include <iostream>
#include <string.h>
#include <vector>

class Grid
{
    private:
        unsigned int r, c;
        std::vector<std::vector<int> *> *grid;

        const int reference_value_01 = 42;
        const int reference_value_02 = 24;
        const int unset = 0;
        int reference_value = reference_value_01;

        typedef struct neighbour
        {
            unsigned int row;
            unsigned int column;
        } neighbour;


    private:
        void init(unsigned int, unsigned int, std::vector<std::vector<int> *> *matrix); 
        void toggle_reference_value(void);
        static unsigned int convert_to_print_value(unsigned int val);
        void mark_island(unsigned int r, unsigned int c);

        void find_neighbours(unsigned int r, unsigned int c, std::vector<neighbour *> *catalog);

    public:
        Grid(unsigned int r, unsigned int c);
        Grid(unsigned int r, unsigned int c, std::vector<std::vector<int> *> *matrix);
        ~Grid(void);
        int q(void);
        void m(unsigned int r, unsigned int c, bool val);
        void print(void);
};

#endif // __GRID_H_INCLUDED__
