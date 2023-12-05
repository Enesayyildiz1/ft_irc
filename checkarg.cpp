#include "headers/checkarg.hpp"

void checkarg::check_args(int ac)
{
    if(ac != 2)
    {
        std::cerr << "Usage <port>" << std::endl;
        exit(1);
    }
}