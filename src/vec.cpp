#include <iostream>
#include <vector>
using namespace std;


int main()
{
    vector<int> s {1,2,3,4};

    cout << "T" << endl;

    for(auto it {s.end()}; it != s.begin(); --it)
    {
        cout << *it << endl;
    }

    return 0;
}