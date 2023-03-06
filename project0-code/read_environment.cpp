// THIS PROGRAM REQUIRES NO MODIFICATION

#include <iostream>
#include <cstdlib>
 
int main(int argc, char* argv[])
{
    const char* uname = std::getenv("USER");
    const char* hname = std::getenv("HOSTNAME");
    const char* home = std::getenv("HOME");

    if (uname && hname && home)
    {
        std::cout << "Your name is:           " << argv[1] << '\n';
        std::cout << "Your username is:       " << uname << '\n';
        std::cout << "Your hostname is:       " << hname << '\n';
        std::cout << "Your home directory is:    " << home << '\n';
    }
    else
    {
        std::cout << "Something went wrong...\n";
    }
}
