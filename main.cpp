#include"headers/Server.hpp"
#include"headers/checkarg.hpp"

int main(int ac, char **av) {
   
   try
    {
    checkarg::check_args(ac);
    Server ircserv("127.0.0.1", av[1], av[2]);
    ircserv.start();
    }
   catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
