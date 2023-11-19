#include <iostream>
#include <ranges>
#include <iterator>

#include <iostream>
#include <vector>
using namespace std;

//template<class T> concept RAI = std::random_access_iterator<T>; //Funktionier nicht für std::vector
template<class T> concept RAR = std::ranges::random_access_range<T>;
template<class T> concept FR = std::ranges::forward_range<T>;


template <typename T>
class RandomAccessContainer {
private:
    std::vector<T> data;

public:
    // Iterator-Klasse
    class Iterator {
    private:
        typename std::vector<T>::iterator current;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = typename std::vector<T>::difference_type;
        using pointer = T*;
        using reference = T&;

        Iterator(typename std::vector<T>::iterator iter) : current(iter) {}

        Iterator() = default;

        // Dereferenzierung
        reference operator*() const {
            return *current;
        }

        // Pfeiloperator
        pointer operator->() const {
            return &(*current);
        }

        // Prä-Inkrement
        Iterator& operator++() {
            ++current;
            return *this;
        }

        // Post-Inkrement
        Iterator operator++(int) {
            Iterator temp = *this;
            ++current;
            return temp;
        }

        // Prä-Dekrement
        Iterator& operator--() {
            --current;
            return *this;
        }

        // Post-Dekrement
        Iterator operator--(int) {
            Iterator temp = *this;
            --current;
            return temp;
        }

        // Addition und Subtraktion
        Iterator operator+(difference_type n) const {
            return Iterator(current + n);
        }

        Iterator operator-(difference_type n) const {
            return Iterator(current - n);
        }

        // Distanz
        difference_type operator-(const Iterator& other) const {
            return current - other.current;
        }

        // Vergleichsoperatoren
        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        bool operator<(const Iterator& other) const {
            return current < other.current;
        }

        bool operator>(const Iterator& other) const {
            return current > other.current;
        }

        bool operator<=(const Iterator& other) const {
            return current <= other.current;
        }

        bool operator>=(const Iterator& other) const {
            return current >= other.current;
        }

        // Inkrement und Dekrement
        Iterator& operator+=(difference_type n) {
            current += n;
            return *this;
        }

        Iterator& operator-=(difference_type n) {
            current -= n;
            return *this;
        }

        // Indexzugriff
        reference operator[](difference_type n) const {
            return *(*this + n);
        }
    };

    // Konstruktor
    RandomAccessContainer(std::initializer_list<T> values) : data(values) {}

    // Iteratoren
    auto begin() {
        return Iterator(data.begin());
    }

    auto end() const
    {
        return Iterator(data.end());
    }
};

int main() {
    RandomAccessContainer<int> container {1, 2, 3, 4, 5};

    //static_assert(RAR<vector<int>>);
    //static_assert(FR<vector<int>>);
    //static_assert(RAR<RandomAccessContainer<int>>);
    static_assert(FR<RandomAccessContainer<int>>);


    // Iteration mit dem Iterator
    for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << std::endl;

    return 0;
}