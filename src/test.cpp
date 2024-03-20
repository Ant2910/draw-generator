#include <iostream>
#include "newurn.hpp"
using namespace urn;
using namespace std;

string to_string(string s)
{
    return s;
}

template<class T>
string to_string(const vector<T>& draw)
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
    GenericUrn<std::string,true,true> u {3,{"A","B","C"}};
    
    for(auto it {u.begin()}; it != u.end(); ++it)
    {
        cout << to_string(*it) << endl;
    }
    
    return 0;
}