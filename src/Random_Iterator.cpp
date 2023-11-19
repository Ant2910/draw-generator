#include <iostream>
#include <ranges>
#include <vector>

// Iterator-Klasse für den benutzerdefinierten Container
class CustomContainerIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = int; // Typ des Container-Elements
    using difference_type = std::ptrdiff_t;
    using pointer = int*;
    using reference = int&;

    CustomContainerIterator(int* ptr) : ptr_(ptr) {}

    CustomContainerIterator() = default;

    // Iteratoren vergleichen
    bool operator==(const CustomContainerIterator& other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const CustomContainerIterator& other) const {
        return !(*this == other);
    }

    // Dereferenzierung des Iterators
    reference operator*() const {
        return *ptr_;
    }

    // Vorwärtsbewegung des Iterators
    CustomContainerIterator& operator++() {
        ++ptr_;
        return *this;
    }

    // Nach vorne bewegen des Iterators
    CustomContainerIterator operator++(int) {
        CustomContainerIterator temp = *this;
        ++(*this);
        return temp;
    }

    // Prä-Dekrement
    CustomContainerIterator& operator--() 
    {
        --ptr_;
        return *this;
    }

    // Post-Dekrement
    CustomContainerIterator operator--(int) 
    {
        CustomContainerIterator temp = *this;
        --(*this);
        return temp;
    }

    // Addition und Subtraktion
    //-------------------
    
    CustomContainerIterator operator+(difference_type n) const //concept header datei anschauen
    {   
        auto temp {*this};
        return (temp += n);
        //return CustomContainerIterator(ptr_ + n);
    }

    friend CustomContainerIterator operator+(difference_type n, const CustomContainerIterator& it) 
    {
        return it + n; // Reusing the operator+ defined earlier
    }
    
    /*
    CustomContainerIterator operator+(const CustomContainerIterator& other) const 
    {
        return CustomContainerIterator(ptr_ + other.ptr_);
    }
    */
    //-------------------
    CustomContainerIterator operator-(difference_type n) const 
    {
        return CustomContainerIterator(ptr_ - n);
    }

    // Distanz
    difference_type operator-(const CustomContainerIterator& other) const 
    {
        return ptr_ - other.ptr_;
    }

    bool operator<(const CustomContainerIterator& other) const 
    {
        return ptr_ < other.ptr_;
    }

    bool operator>(const CustomContainerIterator& other) const 
    {
        return ptr_ > other.ptr_;
    }

    bool operator<=(const CustomContainerIterator& other) const 
    {
        return ptr_ <= other.ptr_;
    }

    bool operator>=(const CustomContainerIterator& other) const 
    {
        return ptr_ >= other.ptr_;
    }

    // Inkrement und Dekrement
    CustomContainerIterator& operator+=(difference_type n) 
    {
        ptr_ += n;
        return *this;
    }

    CustomContainerIterator& operator-=(difference_type n)
    {
        ptr_ -= n;
        return *this;
    }

    // Indexzugriff
    reference operator[](difference_type n) const 
    {   
        auto temp = *this;
        return *(temp + n);
    }

private:
    int* ptr_;
};

// Benutzerdefinierter Container
class CustomContainer {
private:
    std::vector<int> data; // Daten des Containers

public:
    CustomContainer(std::initializer_list<int> list) : data(list) {}

    // Begin-Iterator des Containers
    CustomContainerIterator begin() {
        return CustomContainerIterator(data.data());
    }

    // End-Iterator des Containers
    CustomContainerIterator end() {
        return CustomContainerIterator(data.data() + data.size());
    }
};

template<class T> 
concept R = std::ranges::range<T>;

template<class T>
concept FR = std::ranges::forward_range<T>;

template<class T>
concept BR = std::ranges::bidirectional_range<T>;

template<class T>
concept RR = std::ranges::random_access_range<T>;

  

int main() 
{   
    static_assert(R<CustomContainer>);
    static_assert(FR<CustomContainer>);
    static_assert(BR<CustomContainer>);
    static_assert(RR<CustomContainer>);

    CustomContainer container = {1, 2, 3, 4, 5};

    auto itv = std::ranges::begin(container);
    const auto it = container.begin();
    long int diff = 4;

    std::cout << *(it + diff) << std::endl;
    std::cout << *(diff + it) << std::endl;

    return 0;
}