#include <iostream>
#include <vector>

unsigned long long factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

std::vector<int> findNthDraw(int n, int elements, int drawn) {
    unsigned long long total_variations = factorial(elements) / factorial(elements - drawn);
    std::vector<int> selected;

    if (n < 1 || n > total_variations) {
        return selected; // Die angegebene Ziehung ist außerhalb des gültigen Bereichs
    }

    std::vector<int> nums;
    for (int i = 1; i <= elements; ++i) {
        nums.push_back(i);
    }

    unsigned long long current_variation = total_variations;
    for (int i = 0; i < drawn; ++i) {
        current_variation /= (elements - i);
        int index = (n - 1) / current_variation;
        selected.push_back(nums[index]);
        nums.erase(nums.begin() + index);
        n -= index * current_variation;
    }

    return selected;
}

int main() {
    // Beispiel: 3. Ziehung aus 5 Elementen ohne Wiederholung
    int ordinal_number = 3;
    int total_elements = 5;
    int drawn_elements = 3;

    std::vector<int> result = findNthDraw(ordinal_number, total_elements, drawn_elements);
    if (!result.empty()) {
        std::cout << "Die " << ordinal_number << ". Ziehung aus " << total_elements << " Elementen ohne Wiederholung ist: ";
        for (int num : result) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Die angegebene Ziehung liegt außerhalb des gültigen Bereichs." << std::endl;
    }

    return 0;
}
