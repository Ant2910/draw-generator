#include <iostream>
#include <vector>
#include <exception>
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

uint factorial(const uint& n)
{
    if(n == 0)
    {
        return 1;
    }
    return n*factorial(n-1);
}

uint z(int n, int k)
{
    return ((factorial(n))/(factorial(n-k)*factorial(k)));
}

// Funktion zur Ausgabe einer bestimmten Ziehung für eine gegebene Ordinalzahl
vector<uint> printOrdinalCombination(int n, int k, int ordinal) 
{
    if(ordinal < 0 || ordinal >= z(n,k))
    {
        throw std::domain_error("There is no valid draw for this ordinalnumber.");
    }

    std::vector<uint> combination(k, 0);
    //befüllen des Vektors
    for (int i = 0; i < k; ++i) {
        combination[i] = i; //+ 1;
    }

    for (int count = 1; count <= ordinal; ++count) 
    {
        if (count == ordinal) {
            break;
        }

        int j = k - 1;
        while (j >= 0 && combination[j] == n - k + j + 1) {
            --j;
        }
        ++combination[j];
        for (int l = j + 1; l < k; ++l) {
            combination[l] = combination[l - 1] + 1;
        }
    }
    return combination;
}

int main() 
{
    //Sollte nur eine Ziehung ausgeben!
    cout << to_string(printOrdinalCombination(3, 2, 0)) << endl;
    cout << to_string(printOrdinalCombination(3, 2, 1)) << endl;
    cout << to_string(printOrdinalCombination(3, 2, 2)) << endl;
    cout << to_string(printOrdinalCombination(3, 2, 3)) << endl;

    return 0;
}
