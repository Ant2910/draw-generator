#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
using uint = unsigned int;

string to_string(const vector<uint>& draw)
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
/*
std::vector<uint> ziehungen(int n, int k, int ordinalzahl) 
{
    std::vector<uint> ziehung;

    for (int i = 0; i < k; ++i) {
        ziehung.push_back(i);
    }

    for (int i = 0; i < k; ++i) {
        ziehung[i] += ordinalzahl % (n - i);
        ordinalzahl /= (n - i);
    }

    std::reverse(ziehung.begin(), ziehung.end());

    return ziehung;
}*/

uint factorial(const uint& n)
{
    if(n == 0)
    {
        return 1;
    }
    return n*factorial(n-1);
}

std::vector<uint> ziehungen(int n, int k, int ordinalzahl) 
{
    vector<uint> result;
    vector<uint> elements;
    for(uint fillCount {}; fillCount < n; ++fillCount)
    {
        elements.push_back(fillCount);
    }

    uint currentVariations {(factorial(n)/factorial(n-k))};
    uint index {};
    for(uint upCount{}; upCount < k; ++upCount)
    {
        currentVariations /= (n-upCount);
        index = ordinalzahl/currentVariations;
        result.push_back(elements.at(index));
        elements.erase(elements.begin()+index);
        ordinalzahl -= index*currentVariations;
        if()
    }
    return result;
}


int main() {
    int n = 3; // Anzahl der Bälle
    int k = 3; // Anzahl der zu ziehenden Bälle

    for (int ordinalzahl = 0; ordinalzahl < (factorial(n)/factorial(n-k)); ++ordinalzahl) 
    {
        cout << to_string(ziehungen(n,k,ordinalzahl)) << endl;
    }

    return 0;
}
