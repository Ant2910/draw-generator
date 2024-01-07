#include <iostream>
#include "urn.hpp"
#include "urn.cpp"
using namespace std;
using namespace urn;



int main()
{
    Urn u {4,3};

    do
    {
        for(int i {}; i < 3; ++i)
        {
            cout << u.at(i);
        }
        cout << endl;
    } while (u.next());
    

    return 0;
}