// THIS PROGRAM REQUIRES NO MODIFICATION

#include <iostream>
#include <cstdlib>
 
int main(int argc, char* argv[])
{

    const char* hname = std::getenv("HOSTNAME");


    if (hname)
    {

        std::cout << "Your hostname is:       " << hname << '\n';

    }
    else
    {
        std::cout << "Something went wrong...\n";
    }
}