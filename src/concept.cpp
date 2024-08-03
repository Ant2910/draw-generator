#include <concepts>
#include <iterator>
#include <type_traits>
#include <iostream>
#include "urn.hpp"
#include <vector>
using namespace std;
using namespace urn;

template<typename T>
concept Container = requires(T a) {
    /*    
    typename T::value_type;
    typename T::reference;
    typename T::const_reference;
    typename T::iterator;
    typename T::const_iterator;
    typename T::difference_type;
    typename T::size_type;
    */
    { a.begin() } -> std::same_as<typename T::Iterator>;
    { a.end() } -> std::same_as<typename T::Iterator>;
    //{ a.cbegin() } -> std::same_as<typename T::Iterator>;
    //{ a.cend() } -> std::same_as<typename T::Iterator>;

    { a.size() } -> std::same_as<unsigned int>;
    //{ a.max_size() } -> std::same_as<typename T::size_type>;
    //{ a.empty() } -> std::same_as<bool>;
};

template<typename T>
concept ReversibleContainer = Container<T> && requires(T a) {
    { a.rbegin() } -> std::same_as<typename T::reverse_iterator>;
    { a.rend() } -> std::same_as<typename T::reverse_iterator>;
    { a.crbegin() } -> std::same_as<typename T::const_reverse_iterator>;
    { a.crend() } -> std::same_as<typename T::const_reverse_iterator>;
};

int main()
{   
    cout << "Begin" << endl;
    static_assert(Container<UrnOR>, "std::vector<int> is not a Container");
    //static_assert(ReversibleContainer<UrnOR>, "std::vector<int> is not a ReversibleContainer");
    cout << "End" << endl;


    return 0;
}

