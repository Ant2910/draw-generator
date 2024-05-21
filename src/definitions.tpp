/*! 
 * \file definitions.tpp
 * \author Anton Hempel, Ulrich Eisenecker
 * \date March 18, 2024
 *  
 * File of the definitions of the class/function templates
 */

#include <vector>
#include <string>

using uint              = unsigned int;
using Draw              = std::vector<uint>;

//UrnSelector

template <bool O, bool R>
struct UrnSelector
{
    using UrnType = UrnOR;
};

template<>
struct UrnSelector<true, false>
{
    using UrnType = UrnO;
};

template <>
struct UrnSelector<false, true>
{
    using UrnType = UrnR;
};

template <>
struct UrnSelector<false, false> 
{
    using UrnType = Urn;
};

//Iterator

template<typename T, bool ORDER, bool REPETITION>
GenericUrn<T, ORDER, REPETITION>::Iterator::Iterator(const GenericUrn<T,ORDER,REPETITION>* urn, const uint& ordinalnumber, const Status& status): m_itUrn{ urn },
                                                                                                      m_ordinalnumber{ static_cast<int>(ordinalnumber) },
                                                                                                      m_status { status }{}

template<typename T, bool ORDER, bool REPETITION>
GenericUrn<T, ORDER, REPETITION>::Iterator::Iterator() = default;

template<typename T, bool ORDER, bool REPETITION>
std::string GenericUrn<T,ORDER,REPETITION>::Iterator::status() const
{
    switch(m_status)
    {
        case Status::invalidFront: return "invalidFront"; break;
        case Status::valid: return "valid"; break;
        case Status::invalidBack: return "invalidBack"; break;
        default: throw std::invalid_argument("m_status is invalid."); break;
    }
}

template<typename T, bool ORDER, bool REPETITION>
uint GenericUrn<T,ORDER,REPETITION>::Iterator::n() const
{
    return (*m_itUrn).n();
}

template<typename T, bool ORDER, bool REPETITION>
uint GenericUrn<T,ORDER,REPETITION>::Iterator::k() const
{
    return (*m_itUrn).k();
}

template<typename T, bool ORDER, bool REPETITION>
uint GenericUrn<T,ORDER,REPETITION>::Iterator::size() const
{
    return (*m_itUrn).size();
}

template<typename T, bool ORDER, bool REPETITION>
int GenericUrn<T,ORDER,REPETITION>::Iterator::ordinalnumber() const
{
    return m_ordinalnumber;
}

template<typename T, bool ORDER, bool REPETITION>
const typename GenericUrn<T,ORDER,REPETITION>::Iterator::value_type GenericUrn<T,ORDER,REPETITION>::Iterator::operator*() const 
{   
    if(m_ordinalnumber >= size() || m_ordinalnumber < 0)
    {   
        throw std::domain_error("There is no valid draw for this ordinalnumber.");
    }
    return (*m_itUrn).draw(m_ordinalnumber);
}

template<typename T, bool ORDER, bool REPETITION>
typename GenericUrn<T,ORDER,REPETITION>::Iterator& GenericUrn<T,ORDER,REPETITION>::Iterator::operator++()
{   
    ++m_ordinalnumber;

    if(m_ordinalnumber == 0)
    {  
        m_status = Status::valid;
    }
    else if(m_ordinalnumber < 0)
    {
        m_status = Status::invalidFront;
    }
    else if(m_ordinalnumber >= size())
    {
        m_status = Status::invalidBack;
    }
    return *this;
}

template<typename T, bool ORDER, bool REPETITION>
typename GenericUrn<T,ORDER,REPETITION>::Iterator GenericUrn<T,ORDER,REPETITION>::Iterator::operator++(int)
{ 
    auto temp {*this};
    ++(*this);
    return temp;
}

template<typename T, bool ORDER, bool REPETITION>
typename GenericUrn<T,ORDER,REPETITION>::Iterator& GenericUrn<T,ORDER,REPETITION>::Iterator::operator--()
{   
    --m_ordinalnumber;

    if(m_ordinalnumber == size()-1)
    {  
        m_status = Status::valid;
    }
    else if(m_ordinalnumber < 0)
    {
        m_status = Status::invalidFront;
    }
    else if(m_ordinalnumber >= size())
    {
        m_status = Status::invalidBack;
    }
    return *this;
}

template<typename T, bool ORDER, bool REPETITION>
typename GenericUrn<T,ORDER,REPETITION>::Iterator GenericUrn<T,ORDER,REPETITION>::Iterator::operator--(int)
{
    auto temp {*this};
    --(*this);
    return temp;
}

template<typename T, bool ORDER, bool REPETITION>
bool GenericUrn<T,ORDER,REPETITION>::Iterator::operator== (const typename GenericUrn<T,ORDER,REPETITION>::Iterator::Iterator& other) const
{ 
    return (m_ordinalnumber == other.m_ordinalnumber);
} 

template<typename T, bool ORDER, bool REPETITION>
bool GenericUrn<T,ORDER,REPETITION>::Iterator::operator!= (const typename GenericUrn<T,ORDER,REPETITION>::Iterator::Iterator& other) const
{  
    return !(*this == other); 
}

template<typename T, bool ORDER, bool REPETITION>
bool GenericUrn<T,ORDER,REPETITION>::Iterator::operator< (const typename GenericUrn<T,ORDER,REPETITION>::Iterator::Iterator& other) const
{ 
    return (m_ordinalnumber < other.m_ordinalnumber);
}

template<typename T, bool ORDER, bool REPETITION>
bool GenericUrn<T,ORDER,REPETITION>::Iterator::operator> (const typename GenericUrn<T,ORDER,REPETITION>::Iterator::Iterator& other) const 
{ 
    return (m_ordinalnumber > other.m_ordinalnumber);
}

template<typename T, bool ORDER, bool REPETITION>
bool GenericUrn<T,ORDER,REPETITION>::Iterator::operator<=(const typename GenericUrn<T,ORDER,REPETITION>::Iterator::Iterator& other) const
{ 
    return (*this == other || *this < other);
}

template<typename T, bool ORDER, bool REPETITION>
bool GenericUrn<T,ORDER,REPETITION>::Iterator::operator>=(const typename GenericUrn<T,ORDER,REPETITION>::Iterator::Iterator& other) const
{ 
    return (*this == other || *this > other);
}

template<typename T, bool ORDER, bool REPETITION>
typename GenericUrn<T,ORDER,REPETITION>::Iterator& GenericUrn<T,ORDER,REPETITION>::Iterator::operator+=(const typename GenericUrn<T,ORDER,REPETITION>::Iterator::difference_type& other)
{   
    if(other >= 0)
    {
        for(uint incCount{}; incCount < other; ++incCount)
        {
            ++(*this);
        }
    }
    else if(other < 0)
    {   
        long int positivOther {other * -1};
        for(uint decCount{}; decCount < positivOther; ++decCount)
        {
            --(*this);
        }
    }
    return *this;
}

template<typename T, bool ORDER, bool REPETITION>
typename GenericUrn<T,ORDER,REPETITION>::Iterator GenericUrn<T,ORDER,REPETITION>::Iterator::operator+(const typename GenericUrn<T,ORDER,REPETITION>::Iterator::difference_type& n) const
{ 
    auto temp {*this};
    return (temp += n);
}

template<typename T, bool ORDER, bool REPETITION>
typename GenericUrn<T,ORDER,REPETITION>::Iterator& GenericUrn<T,ORDER,REPETITION>::Iterator::operator-=(const typename GenericUrn<T,ORDER,REPETITION>::Iterator::difference_type& n)
{
    long int negativ {n * -1};
    (*this) += negativ;
    return *this;
}

template<typename T, bool ORDER, bool REPETITION>
typename GenericUrn<T,ORDER,REPETITION>::Iterator GenericUrn<T,ORDER,REPETITION>::Iterator::operator-(const typename GenericUrn<T,ORDER,REPETITION>::Iterator::difference_type& n) const
{ 
    auto temp {*this};
    return (temp -= n);
}

template<typename T, bool ORDER, bool REPETITION>
typename GenericUrn<T,ORDER,REPETITION>::Iterator::difference_type GenericUrn<T,ORDER,REPETITION>::Iterator::operator-(const typename GenericUrn<T,ORDER,REPETITION>::Iterator::Iterator& other) const
{ 
    return m_ordinalnumber - other.m_ordinalnumber;
}

template<typename T, bool ORDER, bool REPETITION>
typename GenericUrn<T,ORDER,REPETITION>::Iterator::reference GenericUrn<T,ORDER,REPETITION>::Iterator::operator[](typename GenericUrn<T,ORDER,REPETITION>::Iterator::size_type index) const 
{ 
    if(index >= size() || index < 0)
    {   
        throw std::domain_error("There is no valid draw for this ordinalnumber.");
    }
    return (*m_itUrn).draw(index);
}

template<typename T, bool ORDER, bool REPETITION>
GenericUrn<T,ORDER,REPETITION>::Iterator::~Iterator() = default;

//GenericUrn

template <typename T,bool ORDER,bool REPETITION>
GenericUrn<T, ORDER, REPETITION>::GenericUrn(uint k, const std::vector<T>& elements):m_urn {static_cast<uint>(elements.size()),k}, 
                                                                                     m_elements {elements}{}
                                                                                    
template <typename T,bool ORDER,bool REPETITION>
uint GenericUrn<T, ORDER, REPETITION>::n() const 
{
    return m_urn.n();
}

template <typename T,bool ORDER,bool REPETITION>
uint GenericUrn<T, ORDER, REPETITION>::k() const
{
    return m_urn.k();
}

template <typename T,bool ORDER,bool REPETITION>
uint GenericUrn<T, ORDER, REPETITION>::size() const
{
    return m_urn.size();
}

template <typename T,bool ORDER,bool REPETITION>
typename GenericUrn<T, ORDER, REPETITION>::Iterator GenericUrn<T, ORDER, REPETITION>::begin()
{
    return Iterator(this,0,Iterator::Status::valid);
}

template <typename T,bool ORDER,bool REPETITION>
typename GenericUrn<T, ORDER, REPETITION>::Iterator GenericUrn<T, ORDER, REPETITION>::end()
{
    return Iterator(this,size(),Iterator::Status::invalidBack);
}

template <typename T,bool ORDER,bool REPETITION>
std::reverse_iterator<typename GenericUrn<T,ORDER,REPETITION>::Iterator> GenericUrn<T, ORDER, REPETITION>::rbegin()
{   
    return std::make_reverse_iterator(end());
}

template <typename T,bool ORDER,bool REPETITION>
std::reverse_iterator<typename GenericUrn<T,ORDER,REPETITION>::Iterator> GenericUrn<T, ORDER, REPETITION>::rend()
{
    return std::make_reverse_iterator(begin());
}

template <typename T,bool ORDER,bool REPETITION>
std::vector<T> GenericUrn<T, ORDER, REPETITION>::to_element(const Draw& draw) const
{
    std::vector<T> result{};
    for(auto i: draw)
    {
        result.push_back(m_elements.at(i));
    }
    return result;
}

template <typename T,bool ORDER,bool REPETITION>
auto GenericUrn<T, ORDER, REPETITION>::draw(uint ordinalnumber) const
{
    return to_element(m_urn.draw(ordinalnumber));
}

template <typename T,bool ORDER,bool REPETITION>
auto GenericUrn<T, ORDER, REPETITION>::nextDraw(const std::vector<T>& draw) const
{   
    Draw nextDraw {};
    for(uint posCount {}; posCount < draw.size(); ++posCount)
    {
        for(uint upCount {}; upCount < m_elements.size(); ++upCount)
        {
            if(draw.at(posCount) == m_elements.at(upCount))
            {
                nextDraw.push_back(upCount);
            }
        }
    }
    return to_element(m_urn.nextDraw(nextDraw));
}

template <typename T,bool ORDER,bool REPETITION>
auto GenericUrn<T, ORDER, REPETITION>::previousDraw(const std::vector<T>& draw) const
{
    Draw backDraw {};
    for(uint posCount {}; posCount < draw.size(); ++posCount)
    {
        for(uint upCount {}; upCount < m_elements.size(); ++upCount)
        {
            if(draw.at(posCount) == m_elements.at(upCount))
            {
                backDraw.push_back(upCount);
            }
        }
    }
    return to_element(m_urn.previousDraw(backDraw));
}

template <typename T,bool ORDER,bool REPETITION>
auto GenericUrn<T, ORDER, REPETITION>::firstDraw()
{
    return to_element(m_urn.firstDraw());
}

template <typename T,bool ORDER,bool REPETITION>
auto GenericUrn<T, ORDER, REPETITION>::lastDraw()
{
    return to_element(m_urn.lastDraw());
}