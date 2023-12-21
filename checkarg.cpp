#include "headers/checkarg.hpp"

void checkarg::check_args(int ac, char **av)
{
    int port  = atoi(av[1]);
    if (ac != 3)
    {
        std::cerr << "Usage <port> <password>" << std::endl;
        exit(1);
    }
    if(port < 1024 || port > 49151)
    {
        std::cerr << "Wrong port number, please enter between of 1024 and 49151";
        exit(1);
    }
}