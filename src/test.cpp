#include <iostream>
#include "newurn.hpp"
using namespace urn;
using namespace std;

string to_string(const Draw& draw)
{   
    string stdraw {};
    for(uint posCount{}; posCount < draw.size(); ++posCount)
    {
        stdraw += to_string(draw.at(posCount));
        if(posCount != (draw.size()-1))
        {
            stdraw += " ";
        }
    }
    return stdraw;
}

int main()
{
    UrnR u {3,3};
    
    for(auto it {u.begin()}; it != u.end(); ++it)
    {
        cout << to_string(*it) << endl;
    }
    
}