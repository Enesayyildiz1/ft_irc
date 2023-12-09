#include "headers/checkarg.hpp"

void checkarg::check_args(int ac)
{
    if(ac != 3)
    {
        std::cerr << "Usage <port> <password>" << std::endl;
        exit(1);
    }
}