#include"headers/Server.hpp"
#include"headers/checkarg.hpp"

int main(int ac, char **av) {
   
    checkarg::check_args(ac);
    Server server(av[1]);
    server.createSocket();
    return 0;
}
