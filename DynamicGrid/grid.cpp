
#include "grid.h"

Grid::Grid(unsigned int r, unsigned int c)
{
    std::vector<std::vector<int> *> *matrix = NULL;

    // TODO
    // fill matrix

    init(r, c, matrix);
}

Grid::Grid(unsigned int r, unsigned int c, std::vector<std::vector<int> *> *matrix)
{
    init(r, c, matrix);
}

Grid::~Grid()
{
    while(!grid->empty())
    {
        auto entry = grid->back();
        grid->pop_back();
        delete entry;
    }
    delete grid;
}

void Grid::init(unsigned int r, unsigned int c, std::vector<std::vector<int> *> *matrix)
{
    if(matrix->size() != r || r == 0)
    {
        //new InvalidParameterException("r is faulty");
    }
    if(matrix->front()->size() != c || c == 0)
    {
        //new InvalidParameterException("c is faulty");
    }
    this->r = r, this->c = c;
    grid = new std::vector<std::vector<int> *>;

    for(unsigned int i = 0; i < r; ++i)
    {
        std::vector<int> *row = new std::vector<int>;
        for(unsigned int k = 0; k < c; ++k)
        {
            row->push_back(matrix->at(i)->at(k));
        }
        grid->push_back(row);
    }
    
}

unsigned int Grid::convert_to_print_value(unsigned int val)
{
    return static_cast<unsigned int>(val?1:0);
}

void Grid::toggle_reference_value()
{
    if(reference_value == reference_value_01)
    {
        reference_value = reference_value_02;
    }
    else
    {
        reference_value = reference_value_01;
    }
}

void Grid::mark_island(unsigned int r, unsigned int c)
{
    auto val = (*(*grid)[r])[c];
    if(val && val != reference_value)
    {
        (*(*grid)[r])[c] = reference_value;

        auto neighbour_catalog = new std::vector<neighbour *>;
        find_neighbours(r, c, neighbour_catalog);

        for(unsigned int i = 0; i < neighbour_catalog->size(); ++i)
        {
            auto n = (*neighbour_catalog)[i];
            mark_island(n->row, n->column);
            delete n;
        }
        delete neighbour_catalog;
    }
    return;
}

void Grid::find_neighbours(
        unsigned int r,
        unsigned int c,
        std::vector<neighbour *> *catalog
    )
{
    if(r-1 >= 0 && r-1 < this->r && c >= 0 && c < this->c)
    {
        auto n = new neighbour{r-1, c};
        catalog->push_back(n);
    }
    if(r >= 0 && r < this->r && c-1 >=0 && c-1 < this->c)
    {
        auto n = new neighbour{r, c-1};
        catalog->push_back(n);
    }
    if(r+1 >= 0 && r+1 < this->r && c >=0 && c < this->c)
    {
        auto n = new neighbour{r+1, c};
        catalog->push_back(n);
    }
    if(r >= 0 && r < this->r && c+1 >=0 && c+1 < this->c)
    {
        auto n = new neighbour{r, c+1};
        catalog->push_back(n);
    }
}

int Grid::q()
{
    int islands = 0;

    toggle_reference_value();

    for(unsigned int r = 0; r < grid->size(); ++r)
    {
        auto row = (*grid)[r];
        for(unsigned int c = 0; c < row->size(); ++c)
        {
            auto val = (*row)[c];
            if(val && val != reference_value)
            {
                mark_island(r, c);
                islands += 1;
            }
        }
    }
    return islands;
}

void Grid::m(unsigned int r, unsigned int c, bool val)
{
    std::vector<int> *row = grid->at(r);
    if(val)
    {
        (*row)[c] = reference_value;
    }
    else
    {
        row->operator[](c) = unset;
    }
    return;
}

void Grid::print()
{
    for(unsigned int i = 0; i < this->r; ++i)
    {
        for(unsigned int k = 0; k < this->c; ++k)
        {

            auto print_val = convert_to_print_value(grid->at(i)->at(k));
            std::cout << print_val;
        }
        std::cout << "\n";
    }
}

