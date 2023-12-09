#ifndef INVOKER_HPP
#define INVOKER_HPP

class Invoker;

#include"Server.hpp"
#include"libraries.hpp"

class Server;



class Invoker
{
    private:



    public:
        Invoker(Server* server);
		virtual ~Invoker();
};







#endif