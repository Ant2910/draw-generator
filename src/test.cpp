#include <iostream>
#include <vector>
using namespace std;

using uint = unsigned int;

unsigned long long factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

string to_string(const vector<int>& draw)
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

std::vector<int> findNthDraw(int n, int elements, int drawn) {
    unsigned long long total_variations = factorial(elements) / factorial(elements - drawn);
    std::vector<int> selected;
    /*
    if (n < 1 || n > total_variations) {
        return selected; // Die angegebene Ziehung ist außerhalb des gültigen Bereichs
    }
    */
    std::vector<int> nums;
    for (int i = 0; i < elements; ++i) {
        nums.push_back(i);
    }

    unsigned long long current_variation = total_variations;
    for (int i = 0; i < drawn; ++i) {
        current_variation /= (elements - i);
        int index = n / current_variation;
        selected.push_back(nums[index]);
        nums.erase(nums.begin() + index);
        n -= index * current_variation;
    }

    return selected;
}

int main() {
    // Beispiel: 3. Ziehung aus 5 Elementen ohne Wiederholung
    int ordinal_number = 6;
    int total_elements = 4;
    int drawn_elements = 3;

    //cout << to_string(findNthDraw(ordinal_number, total_elements, drawn_elements)) << endl;

    cout << to_string(findNthDraw(0, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(1, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(2, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(3, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(4, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(5, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(6, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(7, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(8, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(9, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(10, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(11, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(12, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(13, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(14, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(15, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(16, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(17, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(18, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(19, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(20, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(21, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(22, total_elements, drawn_elements)) << endl;
    cout << to_string(findNthDraw(23, total_elements, drawn_elements)) << endl;


    return 0;
}
